workspace "BwInf_42"
	configurations
	{
		"Debug",
		"Release",
	}
	flags
	{
		"MultiProcessorCompile"
	}
	architecture "x86_64"

	filter "configurations:Debug"
		defines "_DEBUG"

	filter "configurations:Release"
		defines "NDEBUG"

	filter { "system:windows", "configurations:Release", "toolset:not mingw" }
		flags		{ "LinkTimeOptimization" }
	

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
builddir = "%{wks.location}/build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Arukone"

