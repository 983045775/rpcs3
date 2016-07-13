#include "main.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utils/string_ref.h>
#include <eps3/enums.h>
#include <eps3/types.h>

class console_commands
{
	using commands_t = std::unordered_map<utils::string_ref, std::function<void(int argc, char *argv[])>>;

	commands_t m_commands;
	std::string m_input_namespace;
	bool m_exit = false;

public:
	void exit(bool force = false)
	{
		if (force || m_input_namespace.empty())
		{
			m_exit = true;
		}
		else
		{
			m_input_namespace.clear();
		}
	}

	console_commands()
	{
		add("exit", [&](int argc, char *argv[]) { exit(); });
	}

	void add(const utils::string_ref &name, std::function<void(int argc, char *argv[])> callback)
	{
		m_commands[name] = callback;
	}

	void loop()
	{
		std::vector<char> command_args;
		std::vector<char*> command_argv;

		while (!m_exit)
		{
			bool skip_endl = true;

			if (!skip_endl)
			{
				std::cout << std::endl;
			}

			command_args.clear();
			command_argv.clear();
			command_args.reserve(20);

			std::cout << m_input_namespace + ">";
			std::string raw_command;

			if (!std::getline(std::cin, raw_command))
			{
				m_exit = true;
				continue;
			}

			std::string command_storage;
			for (const auto &string : utils::string_ref(raw_command).split())
			{
				command_storage += string.to_string() + " ";
			}

			if (command_storage.empty())
			{
				continue;
			}

			skip_endl = false;

			utils::string_ref command = utils::string_ref(command_storage).trim();

			if (command == "help" || command == "?")
			{
				show_help_for(m_input_namespace);

				continue;
			}

			if (command == "exit")
			{
				exit();

				continue;
			}

			if (!m_input_namespace.empty())
			{
				command_storage = m_input_namespace + " " + command.to_string();

				command = utils::string_ref(command_storage).trim();
			}

			bool is_show_help = false;

			if (command.ends_with("?"))
			{
				is_show_help = true;

				command = command.substr(0, command.length() - 1).trim();
			}

			commands_t::const_iterator found = m_commands.end();
			std::size_t found_count = 0;

			for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
			{
				if (command.starts_with(it->first))
				{
					found = it;
					found_count++;
				}
				else if (it->first.starts_with(command))
				{
					found_count++;
				}

				if (found_count > 1)
				{
					break;
				}
			}

			if (is_show_help)
			{
				show_help_for(command);
				continue;
			}

			if (found_count > 1)
			{
				m_input_namespace = command.to_string();
				continue;
			}

			if (found == m_commands.end())
			{
				std::cout << "unknown command '" << command.to_string() << "'" << std::endl;
				continue;
			}

			for (const auto &string : command.substr(found->first.length()).split())
			{
				command_argv.push_back(command_args.data() + string.to_vector(command_args));
			}

			found->second((int)command_argv.size(), command_argv.data());
			std::cout << std::endl;
		}
	}

private:
	void show_help_for(const utils::string_ref& input_namespace)
	{
		std::cout << "?" << std::endl;
		std::cout << "help" << std::endl;

		for (auto &command_info : m_commands)
		{
			if (command_info.first.starts_with(input_namespace))
			{
				std::cout << command_info.first.substr(input_namespace.length()).trim().to_string() << std::endl;
			}
		}

		std::cout << "exit" << std::endl;
	};
};

void usage(const char *process_name)
{
	std::cout
		<< "usage: " << std::endl
		<< "   " << process_name << " <path-to-elf> [<flags>]" << std::endl
		<< "where: " << std::endl
		<< "   <path-to-elf> - physical path to elf" << std::endl
		<< "   <flags>       - combination of:" << std::endl
		<< "                     -fs - fullscreen mode" << std::endl
		<< "                     -E  - exit on game stop" << std::endl;
}

void unknown_flag(const char *process_name, const char *flag_name)
{
	std::cout << "unknown flag '" << flag_name << "'" << std::endl;
	usage(process_name);
}

#include <Windows.h>

struct dynamic_library
{
	HMODULE m_module = nullptr;

	dynamic_library() = default;

	dynamic_library(const std::string &path)
	{
		open(path);
	}

	~dynamic_library()
	{
		if (opened())
		{
			close();
		}
	}

	void open(const std::string &path)
	{
		m_module = ::LoadLibraryA(path.c_str());
	}

	void close()
	{
		::FreeLibrary(m_module);
		m_module = nullptr;
	}

	bool opened() const
	{
		return m_module != nullptr;
	}

	explicit operator bool() const
	{
		return opened();
	}

	template<typename Type = void *>
	Type get(const std::string &name)
	{
		return (Type)GetProcAddress(m_module, name.c_str());
	}
};

using eps3EmulatorCreate_t = Eps3ErrorCode (*)();

class eps3api_library : dynamic_library
{
	template<typename Type>
	bool load(Type& function, const std::string &name)
	{
		function = get<Type>(name);

		return !!function;
	}

public:
	eps3EmulatorCreate_t create = nullptr;
	eps3EmulatorCreate_t destroy = nullptr;

	eps3api_library() = default;

	eps3api_library(const std::string &path) : dynamic_library(path)
	{
		if (!opened())
		{
			return;
		}

		bool no_errors = true;

		no_errors = no_errors && load(create, "eps3EmulatorCreate");
		no_errors = no_errors && load(destroy, "eps3EmulatorDestroy");

		//no_errors = true;

		if (!no_errors)
		{
			close();
		}
	}

	using dynamic_library::operator bool;
};

int main(int argc, char *argv[])
{
	std::unordered_map<int, eps3api_library> emulators;
	std::string path_to_elf;
	console_commands commands;

	if (argc >= 2)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (argv[i][0] == '-')
			{
				if (!std::strcmp(argv[i] + 1, "h") || !std::strcmp(argv[i] + 1, "help"))
				{
					usage(argv[0]);
					continue;
				}

				if (!std::strcmp(argv[i] + 1, "fs"))
				{
					continue;
				}

				if (!std::strcmp(argv[i] + 1, "E"))
				{
					continue;
				}
			}
			else if (path_to_elf.empty())
			{
				path_to_elf = argv[i];
				continue;
			}

			unknown_flag(argv[0], argv[1]);
			break;
		}
	}

	auto to_int = [](const char *string, int &id)
	{
		bool no_error = true;

		try
		{
			id = std::stoi(string);
		}
		catch (const std::invalid_argument &ex)
		{
			no_error = false;
			std::cout << "bad id. " << ex.what() << std::endl;
		}
		catch (const std::out_of_range &ex)
		{
			no_error = false;
			std::cout << "bad id. " << ex.what() << std::endl;
		}

		return no_error;
	};

	commands.add("emulator create", [&](int argc, char *argv[])
	{
		if (argc != 2)
		{
			std::cout << "bad usage." << std::endl;
			return;
		}

		int id;

		if (!to_int(argv[0], id))
		{
			return;
		}

		if (emulators.find(id) != emulators.end())
		{
			std::cout << "emulator with id " << id << " already exists" << std::endl;
			return;
		}

		std::string path = argv[1];

		auto &library = emulators.emplace(id, path).first->second;

		if (!library)
		{
			emulators.erase(id);
			std::cout << "emulator '" << path << "' not found." << std::endl;
			return;
		}

		Eps3ErrorCode error_code = library.create();

		if (error_code != eps3ErrorOk)
		{
			emulators.erase(id);
			std::cout << "emulator creation error: " << error_code << std::endl;
			return;
		}

		std::cout << "emulator with id " << id << " created" << std::endl;
	});

	commands.add("emulator destroy", [&](int argc, char *argv[])
	{
		if (argc != 1)
		{
			std::cout << "bad usage." << std::endl;
			return;
		}

		int id;

		if (!to_int(argv[0], id))
		{
			return;
		}

		auto found = emulators.find(id);

		if (found == emulators.end())
		{
			std::cout << "emulator with id " << id << " not exists" << std::endl;
			return;
		}

		Eps3ErrorCode error_code = found->second.destroy();

		if (error_code != eps3ErrorOk)
		{
			std::cout << "emulator destroing error: " << error_code << std::endl;
		}

		emulators.erase(found);
	});
	commands.loop();

	return 0;
}
