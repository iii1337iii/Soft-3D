#include "Screen/Main_Cycle.hpp"
#include "Object/Mesh_Data.hpp"
#include "World/Lighting.hpp"
#include "portable-file-dialogs.h"

int main()
{
    if (!pfd::settings::available()) { return 1; }

    render_cycle();

    return 0;
}