#pragma once

#include <utility>

#include "cxxopts.hpp"

namespace argument_parser {


struct Mode {
private:
    const std::string PRI = "PRI";
    const std::string SEC = "SEC";
public:
    const bool secondary;
    const std::string str;
    /*
     * Used for connecting to other dispatcher
     */
    const std::string other_str;

    explicit Mode(bool secondary)
        : secondary(secondary),
          str(secondary ? SEC : PRI),
          other_str(!secondary ? SEC : PRI) {}
};

struct Arguments {
    const Mode mode;
    bool ejector{};
    bool record{};
    bool playback{};
    bool verbose{};
    bool single{};
    std::string filename{};

    explicit Arguments(bool secondary) : mode(secondary) {}
};


namespace argument_names {
static const std::string ofile{"ofile"};
static const std::string record{"record"};
static const std::string ejector{"ejector"};
static const std::string secondary{"secondary"};
static const std::string playback{"playback"};
static const std::string verbose{"verbose"};
static const std::string single{"single"};
}

std::shared_ptr<Arguments> parse(int argc, const char *const *argv);

inline void validate(const Arguments &args) {
    if (args.record && args.playback) {
        std::cout << argument_names::ofile << " and " << " cannot be selected at the same time";
        exit(1);
    }
}

inline std::shared_ptr<Arguments> parse(int argc, const char *const *argv) {
    try {
        cxxopts::Options options(argv[0], " - example command line options");
        options
            .set_width(70)
            .set_tab_expansion()
            .add_options()
                ("h,help", "Print usage")
                ("s," + argument_names::secondary, "start in secondary mode")
                ("v," + argument_names::verbose, "start in secondary mode")
                ("e," + argument_names::ejector, "FTS has ejector instead of switch")
                ("R," + argument_names::record, "enable recording events to file",
                    cxxopts::value<std::string>()->implicit_value(""), "[FILENAME]<optional>")
                (argument_names::single, "do not connect to other dispatcher")
                ("P," + argument_names::playback, "playback a record", cxxopts::value<std::string>(),
                 "[FILENAME]");

        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            exit(0);
        }

        auto args = std::make_shared<Arguments>(result.count(argument_names::secondary));
        args->verbose = result.count(argument_names::verbose);
        args->ejector = result.count(argument_names::ejector);
        args->record = result.count(argument_names::record);
        args->single = result.count(argument_names::single);

        if (result.count(argument_names::record)) {
            args->record = true;
            args->filename = result[argument_names::record].as<std::string>();
        }
        if (result.count(argument_names::playback)) {
            args->playback = true;
            args->filename = result[argument_names::playback].as<std::string>();
        }
        validate(*args);
        return args;
    }
    catch (const cxxopts::OptionException &e) {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        std::cout << "Start with '--help' for usage";
        exit(1);
    }
}

} /* namespace */
