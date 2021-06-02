#pragma once

#include "cxxopts.hpp"

namespace argument_parser {

struct Arguments {
    bool secondary{};
    bool ejector{};
    bool record{};
    bool playback{};
    bool verbose{};
    std::string filename{};
};

namespace argument_names {
static const std::string ofile{"ofile"};
static const std::string record{"record"};
static const std::string ejector{"ejector"};
static const std::string secondary{"secondary"};
static const std::string playback{"playback"};
static const std::string verbose{"verbose"};
}

std::shared_ptr<Arguments> parse(int argc, const char *const *argv);

void validate(const Arguments &args) {
    if (args.record && args.playback) {
        std::cout << argument_names::ofile << " and " << " cannot be selected at the same time";
        exit(1);
    }
}

std::shared_ptr<Arguments> parse(int argc, const char *const *argv) {
    auto args = std::make_shared<Arguments>();
    try {
        cxxopts::Options options(argv[0], " - example command line options");
        options
            .set_width(70)
            .set_tab_expansion()
            .add_options()
                ("h,help", "Print usage")
                ("s," + argument_names::secondary, "start in secondary mode", cxxopts::value<bool>(args->secondary))
                ("v," + argument_names::verbose, "start in secondary mode", cxxopts::value<bool>(args->verbose))
                ("e," + argument_names::ejector, "FTS has ejector instead of switch",
                 cxxopts::value<bool>(args->ejector))
                ("R," + argument_names::record, "enable recording events to file",
                 cxxopts::value<bool>(args->record))
                ("o," + argument_names::ofile, "output file", cxxopts::value<std::string>(),
                 "[FILENAME]")
                ("P," + argument_names::playback, "playback a record", cxxopts::value<std::string>(),
                 "[FILENAME]");

        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            exit(0);
        }
        if (result.count(argument_names::ofile))
            args->filename = result[argument_names::ofile].as<std::string>();
        if (result.count(argument_names::playback)) {
            args->playback = true;
            args->filename = result[argument_names::playback].as<std::string>();
        }
    }
    catch (const cxxopts::OptionException &e) {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        std::cout << "Start with '--help' for usage";
        exit(1);
    }

    validate(*args);
    return args;
}

} /* namespace */
