
#include <string>
#include <cstdlib>

#include <crtUtilities.hpp>

namespace crt
{
    namespace utilities
    {
        void show(const std::string &dotFile)
        {
            std::string basename = dotFile.substr(0, dotFile.find_last_of('.'));
            std::string cmd = "neato -Tpdf \"" + dotFile + "\" -o \"" + basename + ".pdf\"";
            std::system(cmd.c_str());
            std::system(("open \"" + basename + ".pdf\"").c_str());
        }

    }
}
