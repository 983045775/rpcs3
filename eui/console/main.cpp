#include "main.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include <chrono>
#include <utils/string_ref.h>
#include <eps3/enums.h>
#include <eps3/types.h>
#include <eps3/emulator-api.h>
#include <conio.h>
#include <Windows.h>
#include "ui.h"

using namespace std::chrono_literals;

class console_commands
{
	struct command_info
	{
		std::function<void(int argc, char *argv[])> callback;
		std::unordered_map<utils::string_ref, command_info> subcommands;
	};

	command_info m_commands;
	command_info *m_root = &m_commands;
	std::string m_input_namespace;
	bool m_exit = false;
	std::string m_commands_buffer[32];
	std::string m_raw_command;
	std::size_t m_raw_command_offset;

public:
	void exit(bool force = false)
	{
		if (force || m_input_namespace.empty())
		{
			m_exit = true;
		}
		else
		{
			m_root = &m_commands;
			m_input_namespace.clear();
		}
	}

	console_commands()
	{
		add("exit", [&](int argc, char *argv[]) { exit(); });
	}

	void add(const utils::string_ref &name, std::function<void(int argc, char *argv[])> callback)
	{
		auto name_blocks = name.split();

		command_info *info = &m_commands;

		for (std::size_t i = 0; i < name_blocks.size(); ++i)
		{
			info = &info->subcommands[name_blocks[i]];

			if (info->callback)
			{
				std::cout << "registration '" << name.to_string() << "' failed. commands overlaps" << std::endl;
				return;
			}
		}

		info->callback = callback;
	}

	void backspace(std::size_t count = 1)
	{
		if (count > m_raw_command_offset)
		{
			count = m_raw_command_offset;
		}

		for (std::size_t i = 0; i < count; ++i)
		{
			std::cout << "\b \b";
		}

		if (count == m_raw_command.size())
		{
			m_raw_command.clear();
		}
		else if (m_raw_command_offset == m_raw_command.size())
		{
			m_raw_command = m_raw_command.substr(0, m_raw_command_offset - count);
		}
		else
		{
			m_raw_command = m_raw_command.substr(0, m_raw_command_offset - count) + m_raw_command.substr(m_raw_command_offset);
		}

		m_raw_command_offset -= count;
	}

	void left()
	{
		if (m_raw_command_offset)
		{
			std::cout << '\b';
			--m_raw_command_offset;
		}
	}

	void right()
	{
		if (m_raw_command_offset < m_raw_command.size())
		{
			std::cout << m_raw_command[m_raw_command_offset++];
		}
	}

	void home()
	{
		while (m_raw_command_offset)
		{
			std::cout << '\b';
			--m_raw_command_offset;
		}
	}

	void end()
	{
		while (m_raw_command_offset < m_raw_command.size())
		{
			std::cout << m_raw_command[m_raw_command_offset++];
		}
	}

	void set_command(utils::string_ref new_command)
	{
		end();

		backspace(m_raw_command.size());
		m_raw_command = new_command.to_string();
		m_raw_command_offset = m_raw_command.size();
		std::cout << m_raw_command;
	}

	std::string complete(utils::string_ref string)
	{
		if (string.empty())
		{
			return string.to_string();
		}

		auto command_blocks = string.rtrim().split();

		utils::string_ref complete;
		std::size_t count = 0;

		command_info *info = m_root;

		for (std::size_t i = 0; i < command_blocks.size() - 1; ++i)
		{
			auto found = info->subcommands.find(command_blocks[i]);

			if (found == info->subcommands.end())
			{
				//TODO: load files list
				/*
				if (info->callback)
				{
					command_blocks.back();
				}
				*/

				return string.to_string();
			}

			info = &found->second;
		}

		for (auto &entry : info->subcommands)
		{
			if (entry.first.starts_with(command_blocks.back()))
			{
				utils::string_ref new_complete = entry.first;

				if (count == 0 || new_complete != complete)
				{
					if (++count > 1)
					{
						return string.to_string();
					}

					complete = new_complete;
				}
			}
		}

		if (count == 1)
		{
			string = string.rtrim();
			string = string.substr(0, string.size() - command_blocks.back().size());

			std::string final_command = complete.to_string() + " ";
			return string.to_string() + final_command;
		}

		return string.to_string();
	}

	void loop()
	{
		std::vector<char> command_args;
		std::vector<char*> command_argv;

		int currend_command_buffer = 0;
		int command_buffer_count = 0;

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

			currend_command_buffer = command_buffer_count;
			m_raw_command_offset = 0;
			m_raw_command.clear();

			while (int c = _getch())
			{
				if (c == EOF)
				{
					m_exit = true;
					continue;
				}

				if (c == 224)
				{
					c = _getch();

					switch (c)
					{
					case 72:
						if (currend_command_buffer)
						{
							set_command(m_commands_buffer[--currend_command_buffer]);
						}
						break;

					case 80:
						if (currend_command_buffer >= command_buffer_count)
						{
							set_command("");
						}
						else
						{
							set_command(m_commands_buffer[++currend_command_buffer]);
						}
						break;

					case 75:
						left();
						break;

					case 77:
						right();
						break;

					case 71:
						home();
						break;

					case 79:
						end();
						break;

					case 115:
					{
						if (m_raw_command_offset)
						{
							m_raw_command_offset--;
							std::cout << '\b';
						}

						while (m_raw_command_offset)
						{
							m_raw_command_offset--;

							if (m_raw_command[m_raw_command_offset] == ' ')
							{
								m_raw_command_offset++;
								break;
							}

							std::cout << '\b';
						}

						break;
					}

					default:
						continue;
					}

					continue;
				}

				if (c == '\t')
				{
					std::string command = complete(m_raw_command);
					set_command(command);
				}
				else if (c == '\b')
				{
					backspace();

					for (size_t i = m_raw_command_offset; i < m_raw_command.size(); ++i)
					{
						_putch(m_raw_command[i]);
					}

					_putch(' ');

					for (size_t i = m_raw_command_offset; i <= m_raw_command.size(); ++i)
					{
						std::cout << '\b';
					}
				}
				else if (c >= 20 || c == '\n')
				{
					if (m_raw_command_offset >= m_raw_command.size())
					{
						m_raw_command += (char)c;
						m_raw_command_offset++;
						_putch(c);
					}
					else
					{
						m_raw_command.insert(m_raw_command_offset, 1, c);
						for (size_t i = m_raw_command_offset; i < m_raw_command.size(); ++i)
						{
							_putch(m_raw_command[i]);
						}

						m_raw_command_offset++;

						for (size_t i = m_raw_command_offset; i < m_raw_command.size(); ++i)
						{
							std::cout << '\b';
						}
					}
				}
				else if (c == 0xd)
				{
					std::cout << std::endl;
					break;
				}
			}

			if (!command_buffer_count || m_commands_buffer[command_buffer_count - 1] != m_raw_command)
			{
				if (command_buffer_count == std::size(m_commands_buffer))
				{
					for (std::size_t i = 0; i < command_buffer_count - 1; ++i)
					{
						m_commands_buffer[i] = m_commands_buffer[i + 1];
					}

					command_buffer_count--;
				}

				m_commands_buffer[command_buffer_count++] = m_raw_command;
			}

			std::string command_storage;
			for (const auto &string : utils::string_ref(m_raw_command).split())
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
				show_help_for(m_root);

				continue;
			}

			if (command == "exit")
			{
				exit();

				continue;
			}

			bool is_show_help = false;

			if (command.ends_with("?"))
			{
				is_show_help = true;

				command = command.substr(0, command.length() - 1).trim();
			}

			command_info *info = m_root;
			auto command_blocks = command.split();

			std::size_t index;

			for (index = 0; index < command_blocks.size(); ++index)
			{
				auto found = info->subcommands.find(command_blocks[index]);

				if (found == info->subcommands.end() || info->callback)
				{
					break;
				}

				info = &found->second;
			}

			if (is_show_help)
			{
				show_help_for(info);
				continue;
			}

			if (info->callback)
			{
				for (std::size_t i = index; i < command_blocks.size(); ++i)
				{
					command_argv.push_back(command_args.data() + command_blocks[i].to_vector(command_args));
				}

				info->callback((int)command_argv.size(), command_argv.data());
				std::cout << std::endl;
				continue;
			}

			if (info->subcommands.empty())
			{
				std::cout << "unimplemented command '" << command.to_string() << "'" << std::endl;
				continue;
			}

			if (info->subcommands.size() == 1)
			{
				std::cout << "bad command. did you mean '" << command.to_string() << " " << info->subcommands.begin()->first.to_string() << "'?" << std::endl;
				continue;
			}

			if (index < command_blocks.size())
			{
				std::cout << "bad word '" << command_blocks[index].to_string() << "'" << std::endl;
				continue;
			}

			m_input_namespace.clear();
			m_root = info;

			for (size_t i = 0; i < command_blocks.size(); ++i)
			{
				m_input_namespace += command_blocks[i].to_string();
				
				if (i != command_blocks.size() - 1)
				{
					m_input_namespace += " ";
				}
			}

			std::cout << std::endl;
		}
	}

private:
	void show_help_for(command_info* info)
	{
		for (auto &command_info : info->subcommands)
		{
			std::cout << command_info.first.to_string() << std::endl;
		}

		std::cout << std::endl;
	}
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

using eps3EmulatorCreate_t = decltype(&eps3EmulatorCreateImpl);
using eps3EmulatorDestroy_t = decltype(&eps3EmulatorDestroyImpl);
using eps3EmulatorLoad_t = decltype(&eps3EmulatorLoadImpl);
using eps3EmulatorStart_t = decltype(&eps3EmulatorStartImpl);
using eps3EmulatorStop_t = decltype(&eps3EmulatorStopImpl);
using eps3EmulatorPause_t = decltype(&eps3EmulatorPauseImpl);
using eps3EmulatorOnStateChange_t = decltype(&eps3EmulatorOnStateChangeImpl);
using eps3EmulatorGetVersion_t = decltype(&eps3EmulatorGetVersionImpl);
using eps3EmulatorGetVersionString_t = decltype(&eps3EmulatorGetVersionStringImpl);
using eps3EmulatorGetName_t = decltype(&eps3EmulatorGetNameImpl);

class eps3api_library : dynamic_library
{
	template<typename Type>
	bool load(Type& function, const std::string &name)
	{
		function = get<Type>(name);

		return !!function;
	}

public:
	struct
	{
		eps3EmulatorCreate_t create = nullptr;
		eps3EmulatorDestroy_t destroy = nullptr;
		eps3EmulatorLoad_t load = nullptr;
		eps3EmulatorStart_t start = nullptr;
		eps3EmulatorStop_t stop = nullptr;
		eps3EmulatorPause_t pause = nullptr;
		eps3EmulatorOnStateChange_t on_state_change = nullptr;
		eps3EmulatorGetVersion_t get_version = nullptr;
		eps3EmulatorGetVersionString_t get_version_string = nullptr;
		eps3EmulatorGetName_t get_name = nullptr;

	} emulator;

	eps3api_library() = default;

	~eps3api_library()
	{
		if (emulator.destroy)
		{
			emulator.destroy();
		}
	}

	eps3api_library(const std::string &path) : dynamic_library(path)
	{
		if (!opened())
		{
			return;
		}

		bool no_errors = true;

		no_errors = no_errors && load(emulator.create, "eps3EmulatorCreate");
		no_errors = no_errors && load(emulator.destroy, "eps3EmulatorDestroy");

		no_errors = no_errors && load(emulator.load, "eps3EmulatorLoad");
		no_errors = no_errors && load(emulator.start, "eps3EmulatorStart");
		no_errors = no_errors && load(emulator.stop, "eps3EmulatorStop");
		no_errors = no_errors && load(emulator.pause, "eps3EmulatorPause");
		no_errors = no_errors && load(emulator.on_state_change, "eps3EmulatorOnStateChange");
		no_errors = no_errors && load(emulator.get_version, "eps3EmulatorGetVersion");
		no_errors = no_errors && load(emulator.get_version_string, "eps3EmulatorGetVersionString");
		no_errors = no_errors && load(emulator.get_name, "eps3EmulatorGetName");

		//no_errors = true;

		if (!no_errors)
		{
			close();
		}
	}

	using dynamic_library::operator bool;
};

class window
{
	std::unique_ptr<ui::window> m_window;
	std::unique_ptr<ui::context> m_context;
	std::thread m_window_thread;
	std::function<void()> m_custom_task;
	std::atomic<bool> m_has_custom_task{ false };
	std::atomic<bool> m_exit{ false };

public:
	~window()
	{
		m_exit = true;

		if (m_window_thread.joinable())
		{
			m_window_thread.join();
		}
	}

	void create(utils::string_ref title, int width, int height)
	{
		m_window_thread = std::thread([=]
		{
			m_window = std::make_unique<ui::window>(title, width, height);
			m_context = std::make_unique<ui::context>(*m_window.get());

			m_window->show();

			MSG msg;

			while (!m_exit)
			{
				if (!do_custom_task() & !m_window->process_message())
				{
					std::this_thread::sleep_for(1ms);
				}
			}
		});
	}

private:
	bool do_custom_task()
	{
		if (m_has_custom_task)
		{
			m_custom_task();
			m_has_custom_task = false;
			return true;
		}

		return false;
	}

public:
	void set_custom_task(std::function<void()> &&custom_task)
	{
		while (m_has_custom_task);

		m_custom_task = custom_task;
	}
};

class emulator_context
{
	window m_window;
	eps3api_library m_library;

public:
	emulator_context(utils::string_ref path)
		: m_library(path.to_string())
	{
		if (m_library)
		{
			m_window.create("PS3 emulators output", 800, 600);
		}
	}

	eps3api_library& library()
	{
		return m_library;
	}
};


int main(int argc, char *argv[])
{
	std::unordered_map<int, emulator_context> emulators;
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

		auto &library = emulators.emplace(id, path).first->second.library();

		if (!library)
		{
			emulators.erase(id);
			std::cout << "emulator '" << path << "' not found." << std::endl;
			return;
		}

		Eps3ErrorCode error_code = library.emulator.create();

		if (error_code != eps3ErrorOk)
		{
			emulators.erase(id);
			std::cout << "emulator creation error: " << error_code << std::endl;
			return;
		}

		std::cout << library.emulator.get_name();

		char version[32];
		if (library.emulator.get_version_string(version, sizeof(version)) == eps3ErrorOk)
		{
			std::cout << " v" << version;
		}

		std::cout << std::endl;

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

		/*
		Eps3ErrorCode error_code = found->second.emulator.destroy();

		if (error_code != eps3ErrorOk)
		{
			std::cout << "emulator destroing error: " << error_code << std::endl;
		}
		*/

		emulators.erase(found);
	});

	commands.add("executable load", [](int argc, char *argv[])
	{

	});

	commands.add("executable unload", [](int argc, char *argv[])
	{

	});

	commands.loop();

	return 0;
}
