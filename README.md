# An Example CLR Profiler

This repository contains the minimum code required to create a profiler for .NET applications.

The example profiler waits for Garbage Collections, and then writes a message to the standard output of the application it is profiling (the Console, in the case of the example application included).

This code is intended to be used as scaffolding for writing a new CLR profiler and for learning about how these profilers work.

As CLR profilers must be un-managed code, this repository is primarily C++.

## Running the example

- Clone the repository
- Build the solution
- Open a new Command Prompt window
- Run `RunExampleApplication.bat` from the root folder

The batch file first sets some environment variables (see below), before launching a simple Console Application. 

The Console Application's runtime will automatically load the profiler, the code in this sample application has no knowledge of the profiler.

Every 2 seconds, the sample application forces a Garbage Collection. The profiler will receive a notification for this, and write `Profiler: Garbage Collection` to the Console.

> Note: The example batch file assumes you are running on x64 architecture. If you have compiled the application for x86, modify the contents of the batch file to point to the correct output folder

## How CLR profilers work

A CLR profiler is loaded _into the runtime of the application to be profiled_. It does not run as an external process.

Enabling profiling in a .NET application is typically achieved by setting the following environment variables.

```bash
COR_ENABLE_PROFILING = 1                                       # Switch on profiling
COR_PROFILER         = {DF9EDC4B-25C1-4925-A3FB-6AAEB3E2FACD}  # CLSID of the profiler
COR_PROFILER_PATH    = c:\MyProfiler\MyProfiler.dll            # Path to the profiler's DLL
```

Setting these in a Command Prompt window will cause any application launched from that window to load the profiler. If these are set at machine level, _any_ .NET application will run the profiler specified. 

Once the application to be profiled is launched, the CLR will locate the profiler DLL and attempt to load it. If successful, the profiler can subscribe for callbacks when significant events occur (Entering/Leaving methods, Garbage Collections etc.).

The profiler can also modify aspects of the application being profiled. For example, it is possible to subscribe to callbacks that allow you to modify the code in a method.

> Note: It is possible to attach a profiler to an already running .NET process. In this case, however, the scope of what the profiler can do is severely restricted. For brevity, this sample does not include code for attaching to a running process.

## Further reading

This code has been assembled through a combination of MSDN documentation and Microsoft's open-source profiler implementations.

- [MSDN Profiling Documentation](https://msdn.microsoft.com/en-us/library/bb384493(v=vs.100).aspx)
- [Microsoft Archive - CLR Profiler (Github)](https://github.com/MicrosoftArchive/clrprofiler)
- [Microsof Perfview (Github)](https://github.com/Microsoft/perfview)
