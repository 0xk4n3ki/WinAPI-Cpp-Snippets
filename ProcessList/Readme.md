EnumProcesses, EnumProcessMoudles, GetModuleBaseNameA are used to retreive the PiD list and iterate over them to obtain the Module Base name.

LoadLibraryA is being used to load psapi.dll and GetProcAddress to dynamically import the above functions.