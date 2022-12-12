# 📜 Papyrus Debug Adapter

[![](https://vsmarketplacebadge.apphb.com/version-short/joelday.papyrus-lang-vscode.svg)](https://marketplace.visualstudio.com/items?itemName=joelday.papyrus-lang-vscode)
[![Build status](https://ci.appveyor.com/api/projects/status/dpk431rebuplyh45/branch/master?svg=true)](https://ci.appveyor.com/project/joelday/papyrus-debug-server/branch/master)
[![Discord](https://img.shields.io/discord/558746231665328139.svg?color=%23738ADB)](https://discord.gg/E4dWujQ)

Websocket based debug adapter protocol xSE plugin for live Papyrus debugging support. Debug adapter protocol clients connect via the proxy executable found here: https://github.com/joelday/papyrus-lang/tree/master/src/DarkId.Papyrus.DebugAdapterProxy

File any issues here: https://github.com/joelday/papyrus-lang/issues

### Building from Source

NOTE: Fallout 4 doesn't build on this branch currently, only attempt building Skyrim for right now.

Requirements:
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/)
- [vcpkg](https://vcpkg.io/en/getting-started.html)

Make sure you've initialized the submodules in this project, i.e. `git clone --recurse-submodules` when cloning.

1. Install Visual Studio 2022 with C++ support (i.e. "Desktop development with C++" option in the installer)
2. Install vcpkg, and run `vcpkg integrate install` to enable it system-wide.
3. Open the solution in VS2022.
4. Right-click on the Skyrim project, click "Build". This should auto-download and install the required vcpkg dependencies, and then build the project.

When using this with `papyrus-lang`, this goes in the "<Skyrim>/Data/SKSE" folder.

### Acknowledgements

https://github.com/Orvid/Champollion

https://github.com/Samsung/netcoredbg

Special thanks to everyone in the xSE, Modding Tools and Papyrus Language Tools Discord servers.
