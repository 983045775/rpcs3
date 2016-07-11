#include "main.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utils/string_ref.h>

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

using Eps3Emulator = struct Eps3Emulator_s *;
enum Eps3ErrorCode;

using eps3EmulatorCreate_t = Eps3ErrorCode (*)(Eps3Emulator *handle);

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

	eps3api_library() = default;

	eps3api_library(const std::string &path) : dynamic_library(path)
	{
		if (!opened())
		{
			return;
		}

		bool no_errors = true;

		no_errors = no_errors && load(create, "eps3EmulatorCreate");

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

	//emulators.push_back(std::move(rpcs3));

	//char emulator_version[rpcs3api_max_version_length];

	//rpcs3.get_version_string(emulator_version);

	//std::cout << "RPCS3 v" << rpcs3_version << std::endl;
	std::string path_to_elf;

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

				unknown_flag(argv[0], argv[1]);
				break;
			}
			else
			{
				if (path_to_elf.empty())
				{
					path_to_elf = argv[i];
				}
				else
				{
					unknown_flag(argv[0], argv[1]);
					break;
				}
			}
		}
	}

	bool exit = false;
	std::string input_namespace;

	auto do_nothing_impl = [&](...) {};

	auto emulator_create_impl = [&](int argc, char *argv[])
	{
		if (argc != 1 && argc != 2)
		{
			std::cout << "bad usage." << std::endl;
			return;
		}

		int id;

		try
		{
			id = std::stoi(argv[0]);
		}
		catch (const std::invalid_argument &ex)
		{
			std::cout << "bad id. " << ex.what() << std::endl;
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << "bad id. " << ex.what() << std::endl;
		}

		if (emulators.find(id) != emulators.end())
		{
			std::cout << "emulator with id " << id << " already exists" << std::endl;
			return;
		}

		std::string path = argc == 2 ? argv[1] : "./rpcs3.dll";

		auto &library = emulators.emplace(id, path).first->second;

		if (!library)
		{
			emulators.erase(id);
			std::cout << "emulator '" << path << "' not found." << std::endl;
			return;
		}

		std::cout << "emulator with id " << id << " created" << std::endl;
	};

	auto emulator_show_impl = [&](int argc, char *argv[])
	{
		if (argc != 1)
		{
			std::cout << "bad usage." << std::endl;
			return;
		}

		int id;

		try
		{
			id = std::stoi(argv[0]);
		}
		catch (const std::invalid_argument &ex)
		{
			std::cout << "bad id. " << ex.what() << std::endl;
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << "bad id. " << ex.what() << std::endl;
		}

		auto found = emulators.find(id);
		if (found == emulators.end())
		{
			std::cout << "emulator with id " << id << " not found." << std::endl;
			return;
		}

		//found->second.get_version_string(emulator_version);

		std::cout << "eapi emulator v" << "<unknown>" << std::endl;
	};

	auto emulator_start_impl = [&](int argc, char *argv[])
	{
	};

	auto exit_impl = [&](int argc, char *argv[])
	{
		if (input_namespace.empty())
		{
			exit = true;
		}
		else
		{
			input_namespace.clear();
		}
	};

	using commands_t = std::unordered_map<utils::string_ref, std::function<void(int argc, char *argv[])>>;

	static const commands_t commands =
	{
		{ "emulator create", emulator_create_impl },
		{ "emulator show", emulator_show_impl },
		{ "emulator start", emulator_start_impl },
		{ "emulator show", do_nothing_impl },
		{ "emulator stop", do_nothing_impl }
	};

	//std::unordered_map<int, rpcs3::emulator> handles;

	std::vector<char> command_args;
	std::vector<char*> command_argv;

	auto show_help_for = [&](const utils::string_ref& input_namespace)
	{
		std::cout << "?" << std::endl;
		std::cout << "help" << std::endl;

		for (auto &command_info : commands)
		{
			if (command_info.first.starts_with(input_namespace))
			{
				std::cout << command_info.first.substr(input_namespace.length()).trim().to_string() << std::endl;
			}
		}

		std::cout << "exit" << std::endl;
	};

	while (!exit)
	{
		bool skip_endl = true;

		if (!skip_endl)
		{
			std::cout << std::endl;
		}

		command_args.clear();
		command_argv.clear();
		command_args.reserve(20);

		std::cout << input_namespace + ">";
		std::string raw_command;

		if (!std::getline(std::cin, raw_command))
		{
			exit = true;
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
			show_help_for(input_namespace);

			continue;
		}

		if (command == "exit")
		{
			exit_impl(0, nullptr);

			continue;
		}

		if (!input_namespace.empty())
		{
			command_storage = input_namespace + " " + command.to_string();

			command = utils::string_ref(command_storage).trim();
		}

		bool is_show_help = false;

		if (command.ends_with("?"))
		{
			is_show_help = true;

			command = command.substr(0, command.length() - 1).trim();
		}

		commands_t::const_iterator found = commands.end();
		std::size_t found_count = 0;

		for (auto it = commands.begin(); it != commands.end(); ++it)
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
			input_namespace = command.to_string();
			continue;
		}

		if (found == commands.end())
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

	return 0;
}
