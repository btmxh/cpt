#include <argparse/argparse.hpp>

#include <filesystem>
#include <fstream>
#include <istream>
#include <optional>
#include <string>

int main(int argc, const char *argv[]) {
  argparse::ArgumentParser program{"cptpp"};
  std::vector<std::string> include_dirs;
  std::string input_file, output_file;

  program.add_argument("-I", "--include_dir")
      .default_value(std::vector<std::string>{})
      .help(
          "include directories for preprocessing, note that the include "
          "directories for headers not in cpt begin/end blocks are not needed")
      .append()
      .store_into(include_dirs);
  program.add_argument("input")
      .help("input file for preprocessing, leave - for stdin")
      .store_into(input_file);
  program.add_argument("output")
      .help("output file for preprocessing, leave - for stdout")
      .default_value("-")
      .store_into(output_file);

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  std::ifstream input_file_stream;
  std::istream *input_stream = &input_file_stream;
  if (input_file == "-") {
    input_stream = &std::cin;
  } else {
    input_file_stream.open(input_file);
  }

  std::ofstream output_file_stream;
  std::ostream *output_stream = &output_file_stream;
  if (output_file == "-") {
    output_stream = &std::cout;
  } else {
    output_file_stream.open(output_file);
  }

  std::vector<std::filesystem::path> pragma_once_files;
  auto pragma_once_included = [&](const std::filesystem::path &path) {
    for (const auto &included_path : pragma_once_files) {
      if (std::filesystem::equivalent(path, included_path)) {
        return true;
      }
    }
    return false;
  };

  auto preprocess = [&](auto self, std::optional<std::filesystem::path> path,
                        std::istream &is) {
    auto resolve_include_path = [&](std::string_view include_path_str,
                                    bool relative) {
      std::filesystem::path include_path{include_path_str};
      if (include_path.is_absolute() && std::filesystem::exists(include_path)) {
        return include_path;
      }

      if (relative && path) {
        std::filesystem::path candidate =
            path.value().parent_path() / include_path;
        if (std::filesystem::exists(candidate)) {
          return candidate;
        }
      }

      for (const auto &include_dir : include_dirs) {
        std::filesystem::path candidate = include_dir / include_path;
        if (std::filesystem::exists(candidate)) {
          return candidate;
        }
      }

      return std::filesystem::path{};
    };

    std::string line;
    bool in_pragma_section = false;
    while (std::getline(is, line)) {
      std::stringstream line_tokenizer;
      line_tokenizer << line;
      std::string directive;
      line_tokenizer >> directive;
      if (directive == "#pragma") {
        std::string arg;
        line_tokenizer >> arg;
        if (arg == "once") {
          if (path && pragma_once_included(*path)) {
            return;
          }

          if (path) {
            pragma_once_files.push_back(*path);
          }

          continue;
        } else if (arg == "cpt") {
          line_tokenizer >> arg;
          if (arg != "begin" && arg != "end") {
            std::cerr << "WARN: unrecognizable cpt pragma: " << line << '\n';
          }

          if (arg == "begin") {
            if (std::exchange(in_pragma_section, true)) {
              std::cerr << "WARN: nested cpt pragma is not supported" << '\n';
            }
            continue;
          } else {
            in_pragma_section = false;
            continue;
          }
        }
      } else if (directive == "#include" && in_pragma_section) {
        while (isspace(line_tokenizer.peek())) {
          line_tokenizer.ignore(1);
        }

        std::string arg;
        line_tokenizer >> std::noskipws >> arg;
        if (!(arg.front() == '<' && arg.back() == '>') &&
            !(arg.front() == '"' && arg.back() == '"')) {
          std::cerr << "WARN: invalid include directive: " << line << '\n';
        } else {
          bool relative = arg.front() == '"';

          std::string_view include_path{arg};
          include_path = include_path.substr(1, include_path.size() - 2);
          auto resolved_include_path =
            resolve_include_path(include_path, relative);
          if (resolved_include_path.empty()) {
            std::cerr << "WARN: include path not resolved: " << arg << '\n';
          } else {
            std::ifstream include_input_stream{resolved_include_path};
            self(self, resolved_include_path, include_input_stream);
          }
          continue;
        }
      }

      *output_stream << line << '\n';
    }
  };

  std::optional<std::filesystem::path> input_path =
      input_file == "-" ? std::nullopt : std::make_optional(input_file);
  preprocess(preprocess, input_path, *input_stream);
}
