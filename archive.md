Disclaimer:
I am by no means an expert on this topic, but I have successfully cracked some real-life problems so I have some skills.
Also this guide only deals with Windows applications. I imagine the general principles carry over to other OS's but I don't have any experience with it.

This guide is mainly aimed at people who would like to try cracking something and have some technical background, but who do not know where to start.
I've organized the guide into sections. I found it difficult to find a logical order in which to cover everything so it might be a bit of an info dump, sorry about that. Since the sections don't follow a strict order you can skip over ones that don't seem interesting.


First of, what do I mean by "cracking"?
------------------------------------------------
Primarily removing DRM mechanisms to make a game more portable or removing the encryption applied to a set of files. The two often go hand in hand.
A lot of this stuff could also be called "hacking" or "reverse engineering". It's all fairly related. Though with "hacking" I tend to think more of network attacks. Most of the cracking work described here can be done without an active internet connection.


Wait... that's illegal
------------------------
I haven't looked at the specific laws, but yes. Yes it is.
If you're on this forum you probably don't care about that though.
If the moral implications of removing DRM protection bother you, keep in mind that no one is forcing you to release your work. You could do cracking projects and keep the results entirely private, or contact the developers with tips on how to improve their DRM system or some shit*. It's up to you.
If you plan to go into computer security learning how to hack/crack could be quite useful since it teaches you a lot about what makes a system secure.

*Note: Even if you only have good intentions, cracking a game is illegal unless you have prior permission. Don't admit to criminal activity on an account tied to your real identity.


Why crack?
--------------
Personally I do it because I find it fun.
Trying to circumvent a security system is like this great open-world puzzle. Unlike a constructed puzzle which usually only has one or two pre-crafted solutions, this puzzle has tons of potential solutions. Some easy, some ridiculously hard. There is so much freedom and creative control in how you go about solving it.
I find it really rewarding work. And if you succeed it makes you feel like a l33t hacker.


Prerequisite Skills
-----------------------

    General knowledge of how a computer works at the lower level
    Knowing at least one programming language. Preferably a low level one like C++
    A willingness to learn

Ultimately point #3 is the most important. I usually learn a lot about how computers work while trying to crack something. You learn the most by doing, so don't be too discouraged if you don't understand something yet.
That said, if you don't have points #1 or #2 then the initial learning curve will be ridiculously steep. In that case you are probably better off doing some projects focused on learning those general skills before coming back to the topic of cracking.
Knowing how to program is important since a lot of methods required you to write and compile a program. A language like C++ is most useful for "actual" cracking work, but a high-level language such as Python is also very useful to automate any miscellaneous tasks that come up.


Useful tools
---------------
Notepad++ (https://notepad-plus-plus.org/)
(plain-text editor)
Use:​
- Taking notes​
- General purpose text editing​
- Viewing files that are mostly text​
​
Notes:​
- There is a button for "show all characters". This will show whitespace characters and line-endings. Use it whenever you want to be sure that you are seeing the full file.​
- Check the "Encoding" menu. Some mostly-text files won't display properly if you use the wrong encoding.​


HxD (https://mh-nexus.de/en/hxd/)
(hex-editor)
Use:​
- View binary data of any file​
- Check for differences between two files or just check if two files are identical​
- Can manually edit files in a pinch​
​
Notes:​
- Has side-tab that shows ascii encoding of data. Lets you scan through files for readable strings, which are more common than you might think.​


Dependency walker (https://www.dependencywalker.com/)
(gives information on .dlls and exes)
Use:​
- Lets you see which .dlls are statically linked, which files get imported, and most importantly, which functions a exe/dll exports​


Fiddler 4 (https://www.telerik.com/fiddler)
(Gives information on web traffic)
Use:​
- Lets you see which web requests are being made on your machine​
- Also lets you decode requests or setup automated responses​
​
Notes:​
If you really want to get into the network side of things there's also WireShark which does similar things but is more complex​


ILSpy (https://github.com/icsharpcode/ILSpy)
(Decompiler for managed code)
Use:​
- Let's you decompile managed code into a (from my experience) quite readable result​
​
Notes:​
Unity applications use C# which compiles to managed code.​
Other than that most applications use unmanaged code though so you might not get much use out of this one.​


x64dbg (https://x64dbg.com/)
(General purpose debugger)
Use:​
- Let's you see which assembly code a program is running and step through the code​
- Also lets you see which modules are loaded, what the memory space looks like, and which threads are running​
​
Notes:​
Some applications can only be latched onto if you are running the debugger in admin mode.​
​
Many applications you will encounter (especially dedicated DRM systems) will check for a debugger and shutdown if one is found. Of course, checking for a debugger still requires code to be executed, so if you are stepping through the program line-by-line you can probably do something to prevent the debugger check from triggering. But there is a LOT of assembly code so it most cases you want to run until a breakpoint or until a function returns and in those situations you often find that a debugger check got triggered somewhere and shut everything down.​
​
So is the debugger useless for those applications then? Not at all.​

    You can latch onto an application after it is running, so debugger-checks in the start-up phase are bypassed
    The process is paused when the debugger latches on, so you get a snapshot of the program at that time which you can analyze for as long as you wish. (and you can use hooks to pause the program and latch on during a moment of interest. More on hooks later)
    Debugger checks don't happen constantly. You might be able to step through quite a bit of code before encountering one.
    If the program uses the IsDebuggerPresent windows function, then you may be able to hook it and disable the checks that way.

​
Warning:​
I only started using a debugger in my workflow fairly recently and found it incredibly helpful. However my advice regarding it's use and assembly language in general might not be optimal since I'm still learning.​


Process Explorer (https://docs.microsoft.com/en-us/sysinternals/downloads/process-explorer)
(kinda like taskmanager but with more features)
Use:​
- Lets you view which processes are running, what their PID's are, and kill them​
- Lets you perform dumps for processes​
- Lets you see the settings for how a process was started​
- Lets you view the environment variables for a process​
- Has a feature for detected strings found in the process memory​
​
Notes:​
I've had one instance where a process couldn't be killed with Task Manager but Process Explorer could. Something to keep in mind​


Process Monitor (https://docs.microsoft.com/en-us/sysinternals/downloads/procmon)
Use:​
- Let's you view file-reads, file-write, registry access, dll loads, and a few other event types​
- For each event, also gives you the stack-trace of the program at that time​
​
Notes:​
Together this can tell you a lot about what the program is doing.​
​
Example 1:​
You have an archive file of an unknown format and you see the program do something like:​
- Read a bit in section A​
- Suddenly do a far jump and read a block of data in section B​
Then section A is likely an index of some sort and section B holds the raw file data.​
Try extracting the data block that got read from section B and see if it's readable.​
If not there is probably a second decryption or decompression step applied.​
​
Example 2:​
You see the program read through an entire file in equal-sized chunks.​
The program is probably performing some sort of integrity check on the file.​
​
Example 3:​
You see the program make a failed registry access under a program-specific name​
If it's a registry "folder", try creating it and seeing how the program responds.​
If you're lucky the program may be trying to read a "IsVerified" value which you can just set to 1 (true)​
Admittedly, this DRM setup would be pretty dumb, but there are a lot of dumb DRM setups out there. It's worth trying the simple stuff.​
​
Warning:​
Similar to using the debugger, you have a problem with information overload here.​
Programs will trigger a ton of events and most of them are not noteworthy.​
The first time I used Process Monitor I saw it making an access to a cryptically named registry key and thought "Aha! That's where the encryption key is stored!". But no, it was just one of the registries that gets accessed during normal execution of windows programs.​
It might be worthwhile looking at a simple program like say notepad just to get an idea of what the baseline level of event spam is.​


Visual Studio (https://visualstudio.microsoft.com/)
(Programming IDE)
Use:​
- Program stuff!​
- Let's you open projects others have created. If it's a windows application they usually use Visual Studio​


A quick note about managed vs unmanaged code
--------------------------------------------------------------
Most applications compile down to assembly code which can be run directly. This is called "unmanaged code". However some languages that use the .NET framework like C# compile down to an intermediate language (aka IL) which gets executed by a different program. .exe and .dll files may contain managed or unmanaged code and depending on which need to be dealt with differently.
Google it if you want more information.


A quick note about DLLs
-------------------------------
If you are not familiar with DLLs, here's a short primer:
DLLs and EXEs are pretty similar. They both contain code, expect .exe's are meant as a starting place for a program to run. DLLs get included/used by other programs.
DLLs have a list of "exported" functions which maps string names to function addresses in the DLL. "Exported" functions make up the interface by which the DLL is meant to be used. You can technically call any function a DLL has, but you need to know where it is located in memory. Hence the exports are there to tell you.
To call a function you also need to know what the function signature is (calling convention, return type, and argument types). The export table does NOT give you this information, you have to rely on external documentation for this. Any DLL that's meant to be usable by the general public will have documentation available.


Cracking Technique: DLL injection
-------------------------------------------
Dll injection lets you force an application to load a dll of your choice.
Dll's can execute code when they are loaded by a process so this allows you to execute arbitrary code within the process of your choice.
There are a few ways of getting an application to load your DLL, but the simplest two methods are:

    Launch the victim application in a suspended state, inject the dll using a remote thread, resume the victim process
    With an already running victim process, inject the dll using a remote thread

Personally I prefer #1 because with the application in a suspended state you get to execute your code before anything else happens. Gives you more control.
Alternatively method #2 is nice if there is something preventing you from launching the application via code or you want to wait for some initialization code to finish.


General Cracking Technique: Hooking
------------------------------------------------
Hooking allows you to overwrite the behavior of any function for which you know the address and function signature.
If this sounds really powerful it's because it is. I don't know if there's a way for applications to prevent you from hooking them, but if there is I haven't encountered it. Be the hooker you've always wanted to be be!
Hooking works by changing the assembly instructions loaded in memory. I'd advise reading up on it, it's quite interesting.
The high level explanation is that when anything calls function X, it instead calls your function X' which can run whatever code it wants including calling the original function X.

Here's a usage example that's not too far fetched,

Problem:
You have an application with a bunch of encrypted data files. The application is using a custom encryption method and you don't know how it generates the key.
However it comes with a DLL "crypto.dll" that contains the encryption code. This DLL exports the function "decrypt". To keep things simple, let's say that you know that the function signature is:
void __stdcall decrypt(void* buffer, int length, char* key)

Solution:
Inject a dll into the victim process that hooks crypto.dll's "decrypt" function and replace it with a function that prints the key to a file. Now that you have the key, you can call crypto.dll's decrypt function to decrypt any file you wish! It could be using the worlds most complex encryption scheme, it doesn't matter. You don't need to know how the decryption works. It just works.

Now in practice, there are a few things that can make this more complicated:
1. If an external library like "cryto" is used, it probably won't export any critical functions. The dev knows where the functions are and can call them, no one else needs to know​
2. You probably won't know the function signature. However this is something you can overcome. More on this later.​
3. The DLL may run some initialization code necessary for decryption to work. Maybe it has an init(specialKey) function and later inputted keys get XORed with the special key before decryption takes place.​
However, in this case you could either:​
- Hook init(specialKey) as well​
or​
- Run your decryption code within the victim process using the pre-initialized crypto.dll library​


The technical details
--------------------------
Now you might be wondering: Ok that's nice and all, but how do I actually do this?
All this information is available online, so you can just google it, but since I'm trying to be helpful here I'll also go over some of the methods in exact detail.

When I first learnt to be a hooker I used a C# library called EasyHook. This works, sort of, and you can give it a go if you really like C#, but I'd advise using C++ instead.
Reasons for using C++ instead of C#:

1. C# is managed code so you are injecting managed code into an unmanaged application. This works in most cases but I think it can cause some strange behavious depending on what you hook. I had an issue with hooks failing which went away once I switched to C++​
​
2. With C++ it's much easier to accurately describe function signatures. For example if you look at the windows API function GetProcAddress you'll see the signature is: FARPROC GetProcAddress(HMODULE, LPCSTR)​
​
Now you might be wondering: Wtf is an HMODULE, what is an LPCSTR? whats FARPROC?​
If you go digging a bit you find that:​
FARPROC can be treated as void*​
HMODULE can be treated as void*​
LPCSTR is CHAR* is char*​
​
Now you need to find all the C# equivalents to construct the signature definition, and if you make any mistakes it won't work.​
With C++ you just import Window.h and use the LPCSTR crap directly. In visual studio you can also hover over the type to see what the underlying type is. And if you use the type incorrectly you'll probably get a compiler error. Regardless, you can be sure that your function signature is accurate to the documentation.​

So ya, save yourself some pain and use C++

Anyways, let's say you want to hook an application and log when it writes to a file.
Boot up visual studio and create a new C++ console app project, lets call it "Injector".
Add a new project to your solution, this time a C++ dll, lets call it "InjectionDll".
If "Injector" is not in bold, right-click it and set it as the "startup project".
Also right-click it go Build Dependencies > Project Dependencies and set InjectionDll as a dependency.
Now when you hit the start button, both projects will build (if necessary) and "Injector" will run.

As I'm writing this, I think I'm going to include this demo program with the post instead of writing it all out here. I'll just go over the high-level points here.

Write the code to do the dll injection yourself. At first I looked for a library for it, but it's actually easy as shit. (only like 30 lines of code)
Steps are:
- Get a handle to your victim process with necessary permissions (may need to run in admin mode depending on what you are targeting)​
- Get address of LoadLibraryA​
- Allocate memory in the victim process and copy the path to your injection dll​
- Create a remote thread that calls LoadLibraryA with the path to your injection dll as the argument​
(since the argument is actually a pointer, we had to load the string data into the victim process first)​
- Wait for the remote thread to finish​
- Close the process handle and free allocated memory (or don't, the DLL injection is done at this point)​

If you are using injection method #1, you add the wrapper steps:
- Launch exe in suspended state (requires the file path), returning a handle​
- Other steps​
- Release exe from suspended state​

If you are using injection method #2, you add the wrapper steps:
- Get handle to running process (requires the PID), returning a handle​
- Other steps​

And that's all the Injector needs to do.
You can copy-paste the Injector code for each cracking project you do or setup something fancy that re-uses the same project for everything.

For the InjectionDll, the entry-point is the function called DllMain.
To start out with, just write a message to a file and confirm that the DllMain code is being called.

To perform the hooking I use a library called MinHook (https://www.codeproject.com/Articles/44326/MinHook-The-Minimalistic-x-x-API-Hooking-Libra)
There are other hooking libraries out there, but I'll just be covering MinHook here.
Install MinHook in your dll project and call MH_Initialize() to make sure that works.

The general process for creating a hook is:
- Create a typedef for the function handle.​
- Create a global variable for holding the original function pointer​
- Create a function with the same signature that will be called instead​
- Call MH_CreateHook to make the hook​
- Call MH_EnableHook to enable it (don't forget this step)​

In our example, the code is:

C:

typedef BOOL (__stdcall* WriteFileDef)(HANDLE, LPCVOID,DWORD,LPDWORD,LPOVERLAPPPED);
WriteFileDef WriteFileOriginal = NULL;

BOOL WriteFileDetour(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped){
    // TODO Perform logging code here

    // Call original function so host program proceeds unhindered
    return WriteFileOriginal(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

void hookWriteFile(){
    if(MH_CreateHook(&WriteFIle, &WriteFileDetour, &WriteFileOriginal) == MH_OK){
        // Created successfully
        if(MH_EnableHook(&WriteFile) == MH_OK){
            // Success!
        }
        else{
            // TODO: Print error message
        }
    }
    else{
        // TODO: Print error message
    }
}

Then to apply the hook you just call hookWriteFile() in DllMain after calling MH_Initialize()

MinHook identifies hooks by the address they target.
In this situation we are hooking a part of the windows API that is always available, so we can just use &<Name-Of-Function>
In many situations you will be hooking a function from a dll. Let's pretend ReadFile is part of a dll called external.dll. In that case the hooking code would be:


C:

void* hookAddr = (void*)GetProcAddress(GetModuleHandleA("external.dll"), "ReadFile");
MH_CreateHook(hookAddr, &WriteFileDetour, &WriteFileOriginal);
MH_EnableHook(hookAddr);

Note that for this to work, "external.dll" needs to be loaded by the process.


What if my target dll is not loaded?
--------------------------------------------
Two options:

    Just load it yourself by calling LoadLibrary()
    When the host process tries to load it again later it will just return a handle to the already loaded process.
    Hook LoadLibrary and wait for the host process to load the target dll. Load it, then setup your hooks before returning.


Pitfall: Wide Character vs Narrow Characters
----------------------------------------------------------
As you may know, in C++ there are "normal" characters (char) and wide characters (wchar_t)
char is 1 byte (and often gets used to just represent non-text binary data) while wchar_t is two bytes.
In the context of text, char is used for ascii characters while wchar_t is for unicode and other broader character sets.
If you have a file with a Japanese character in the name you'd want to use a wide character string to represent the path.

Anyways, basically all windows API calls that involve text have a wide and "narrow" version.
The wide version has a W postfix while the narrow/ascii version has an A postfix.
The default version of all API calls is the wide version.
For example if you see LoadLibrary("x.dll") it's actually LoadLibraryW("x.dll"). LoadLibrary is a macro that expands to LoadLibraryW

A call to LoadLibraryA and an equivalent one to LoadLibraryW will resolve to some common function down the line, but I prefer not to hook stuff that is super low-level.
If you want to monitor every library that gets loaded, just hook both LoadLibraryA and LoadLibaryW.
Same idea applies to the other API functions.


Pitfall: Incorrect calling convention
---------------------------------------------
If you get the calling convention of a function wrong you will get a quite helpful error message that says something about the ESP register and suggests you fucked up the calling convention.
There are a few calling conventions, but the two I seem to encounter constantly are __stdcall and __cdecl.
A function definition that specifies the calling convention looks like:

C:

void __stdcall funName(...){
    ...
}

If you are hooking a documented API it will tell you which calling convention to use, often specified via macro.
For example the windows api has the WINAPI macro that expands to __stdcall


Using macros to write hooks faster
--------------------------------------------
You may notice that there is a lot of repetition when writing a hook. You need to write out the function definition twice and create multiple similarly named types and objects.
Well, you can setup some macros to speed-up the process. I'll include the macros I'm currently using in the demo project. In short they allow you to write out a hook like this:

C:

HOOK_DEF(LoadLibraryW, __stdcall, HMODULE, LPCWSTR moduleName) {
    // Do something
    return fp_LoadLibraryW(moduleName)
}

CREATE_HOOK_SIMPLE(LoadLibraryW)

And then install it somewhere by calling: hookLibraryW()


Getting feedback from your injected DLL
----------------------------------------------------
The injected DLL can't print to the console window (unless your target application has one open), so how do you get feedback?
A simple solution is writing to files, which is the approach I'd recommend for new people.
A complicated solution is using inter-process-communication (IPC) to send the data to another application which is also running. This allows you to send data to another application which has a console window open, giving you feedback in real time. It's quite pretty once setup.
You could also use this to send data to your injected DLL, though I can't think of many applications for doing that.


Hooking undocumented functions
--------------------------------------------
When hooking a function, the things you want to know, in order of importance, are:
1. The function address​
2. The function signature​
3. What the function does & what the arguments mean​

When hooking a documented API you usually know all three but sometimes you aren't so lucky.
Let's go through them in order:

Case 1: I don't know anything
--------------------------------------
At the very minimum you need to know what your looking for.
Usually this goes something like "I think there is a function that does X, I want to hook it"
Let's say you are trying to remove a DRM check. You speculate that the program has a function like IsUserAuthorized() which just returns a boolean value. You want to hook this function and have it always return true.
To make this more challenging, lets also say that the program uses aggressive debugger checking, so stepping through the assembly code for any extended length of time is not an option.

The first step is to analyze where this function call is taking place. Look at the events triggered by process monitor and see if you can determine a region where the DRM check is likely happening. Lets say you determine that while the DRM check is happening a public API function X is being called.
Hook function X and make the thread sleep for, say, 15 seconds, then return the proper value. This way you are ensuring that the IsUserAuthorized() function is running for at least 15 seconds. Launch the program (with the hook) and within that 15 second window, latch on with the debugger.
The program is now paused within the DRM check and you can analyze to your hearts content.
(Note: There are usually a lot of threads running. Make sure you are looking at the correct one)

Look at the stack trace and hop around looking at the functions that are currently active. IsUserAuthorized is probably somewhere near the top (assuming it exists).
This step is obviously easier the more you know about assembly.
I'm not great at assembly myself so I don't want to give too much advice on it here, but two keys things to note are:
1. Arguments to a function get added by pushing them to the stack. If you see X "push" commands before a function call, the function probably takes X arguments.​
2. Function definitions usually have some "blank" space before them in the form of "INT3" instructions​

Once you find a candidate function, note down it's address. (that is, the address of the first instruction in the function) If the function is within the memory space of a module, write down the base address of the module.
You can also use the raw address directly, but it is less reliable because modules are not guaranteed to be loaded in the same place.

Congratulations! You can now move on to the next stage

Note of caution:
As far as my understanding goes, not all assembly level functions can be hooked seamlessly.
"Proper" functions follow some rules like not modifying the registers. At the assembly language level anything goes. You could have an assembly-level function that modifies registers and external code that depends on the registers being modified. In that case adding a "proper" function wrapper breaks the code since the wrapper function will restore registers to their original value preventing the internal function from having the same effect.


Case 1.5: I have a candidate address, but I'm not sure
-------------------------------------------------------------------
Setup a hook for a function that takes no arguments. In that function make the thread for sleep for 15 seconds.
Run the program and latch on with the debugger once it hangs. (If it doesn't hang at all, your address is completely incorrect) Take a look at the call stack and the arguments loaded into the stack to ensure everything looks about as expected.

Side note:
The code for calculating a raw address looks like:
void* address = (DWORD)GetModuleHandleA("baseModule") + (DWORD)0x187a0

There are probably a few ways to format it, but that's the method that's worked for me.


Case 2: I know the address and nothing else
-------------------------------------------------------
The sophisticated method would be to learn enough about calling conventions and assembly that you can just look at the assembly and go "ah, this takes X arguments and uses calling convention Y, of course". But for those of us who are too dumb or lazy to do that, the following method also works.

You can experimentally figure out how many arguments a function takes.
This may be wrong, but I think when dealing with 32bit applications, every "type" can just be seen as a 32 bit value.
So incrementally try:
UINT32 __stdcall funName()
UINT32 __stdcall funName(UINT32 arg0)
UINT32 __stdcall funName(UINT32 arg0,UINT32 arg1)
etc.

In each case, just call the original function, return the value, and do nothing else.

From my experience:
- If you get the number of arguments wrong, the program will just crash without any error message or a very generic one.
- If you have the number of arguments right but the calling convention wrong, you will get an error message telling you you're using the wrong calling convention
- If you have the function signature right and you're not hooking a weird assembly-level function, then the program will run like normal!

So, add arguments until you get a calling convention error, then cycle calling conventions until the errors stop.
If you reach 10+ arguments, check your assumptions. It's very unlikely for a function to have that many arguments.


Case 3: I know the address and signature but not what it does
------------------------------------------------------------------------------
Start analyzing the function by printing the arguments and the returned value (from the original function) as hex values.
If the value is relatively low, it's probably a raw value. If it's high it's probably a pointer of some sort.

To figure out pointers, latch on with the debugger and check where in memory the potential pointer is pointing. If it points to a section of 0 bytes, it's probably not a pointer. Similarly, if it points to the middle of a section that looks completely random, then it's probably not a raw pointer either.
If you're lucky, you can recognize some data in the area the pointer is pointing to.

You should also try stepping through the function with the debugger if you're able to. Make note of values that come up and see where they re-appear.


Primer on XOR
-------------------
If you aren't familiar with the XOR operation (also written: ^), the key properties are:
1. It's a bitwise operation, meaning the inputs and outputs are the same length​
2. A ^ B = B ^ A​
3. A ^ (B ^ C) = (A ^ B) ^ C​
4. A ^ A = 0 (ie, a sequence of 0 bits as long as A)​
5. A ^ 0 = A​

Security systems love xor-ing shit so it's a good operation to be familiar with.


Regarding Encryption Systems
---------------------------------------
Quick primer on terminology:
Plaintext = Unencrypted binary data (doesn't have to represent text)
Ciphertext = Encrypted binary data
Block size = Smallest unit that encryption algorithm can work on
For some algorithms this is 1 byte or even 1 bit making them essentially blockless

Encryption systems can have a few properties.
Let's go over a few:

    XORing the plaintext to the ciphertext results in a repeating sequence (or one with a clear pattern) (VERY WEAK)
    XORing the plaintext to the ciphertext results in a non-repeating random sequence
    2a. ...but this sequence is the same for any plain-cipher pair
    2b. ...and this sequence is unique for any plain-cipher pair
    Blocks of plaintext data (often 16 bytes) that are equal get mapped to equal ciphertext blocks
    The smaller the blocksize is, the more relevant this property is.
    Equal plaintext files get equal ciphertext files
    Plaintext results in a ciphertext of equal size (pretty common)

Assuming you get your hands on some plaintext-ciphertext pairings, most of these properties are pretty easy to check so I'd recommend doing so.
If your properties are:
XORing results in no usefull data (2b)
Equal blocks don't necessarily map the same (not 3)
Equal files map the same (4) (hard to check though)

Then you are probably dealing with AES in CBC mode.
I'll go over AES in more detail than you probably want in the next section.
The mini-summary is:

    To decrypt a file you need the key.
    To fully decrypt files you also need to know the IV and how it deals with non-block aligned data, but those two are relatively simple to figure out.
    AES is a very secure standard. You won't figure out any useful information on the key by looking at plaintext-cipher pairs. The key is also too long to brute force (assuming it got generated in a random way).


AES, how does it work?
-----------------------------
AES uses a key length of 128, 196, or 256 bits.
It has a block size of 128 bits.

Let examine AES in two levels of detail:

AES Level 1:
----------------
Let's just abstract away the details of how a block gets processed and view it as two functions:
encrypt(key,plain-block) = cipher-block​
decrypt(key,cipher-block) = plain-block​
(where decrypt(key,encrypt(key,x)) = encrypt(key,decrypt(key,x)) = x)​

It's important to remember that encrypt/decrypt only works on binary sequences that are exactly 128 bits long (the block size)
The main two modes of AES, ECB & CBC, that I will go over take the general approach of breaking the input up into block-sized chunks and running encrypt/decrypt on each chunk.
But what if the input sequence is not divisible by the block size? Then you have some 1-127 bits leftover that still need to be dealt with.

Few ways to deal with this:

    Just don't encrypt it lol
    This is a dumb but simple approach. It's bad on a matter of principle since encryption-schemes are meant to encrypt, not leave plain spots. However in some situations it may not matter. Knowing the last 127 bits of an exe doesn't get you very far if your goal is to run it. That said, I've never seen this approach used in the wild.

    Use a different encryption scheme for the last part that does not have the block-size restriction
    There are a lot of encryption schemes out there that don't have the block-size restriction, including some variants of AES.
    Often encryption schemes aren't too complicated when run on very short sequences of data. The whole system may simplify down to XORing the remaining X bits with the first X bits of a static sequence.

    Pad the data so that it fills the block
    There are a couple of padding schemes out there, but they all boil down to the general idea of: Pad with bytes and make the last byte indicate how many bytes of padding there are.
    Note that with padding schemes that don't rely on externally stored data, the data will always be padded even if the plain-text is divisible by the block size. This is because the last byte is reserved to indicate how much padding there is, it can't be part of the plain-text as well.


Right, so assuming the data has been adjusted so it can be represented as a sequence of blocks, how do we encrypt it?
(For the following sections plainX means "Xth block of plaintext" and cipherX means "Xth block of ciphertext")

ECB Mode
--------------
For AES using ECB mode:
cipher1 = encrypt(key,plain1)
cipher2 = encrypt(key,plain2)
...
cipherN = encrypt(key,plainN)

So just encrypt each block separately.

This has the weakness that identical blocks will always get encrypted the same way. If you have access to some plain-cipher pairs then you may be able to partially decrypt a different file by seeing which cipher blocks match ones from your known set.
You also know that if two cipher files have equal cipher blocks in a location, then the plain-text files are identical for those blocks.
That said, if your goal is to decrypt the whole file, ECB mode doesn't really help you. You're still gonna need the key.

For practical purposes ECB mode is useful since for one-block inputs it is identical to the underlying encrypt/decrypt functions upon which the other AES modes are built.

CBC Mode
--------------
Unlike ECB, AES in CBC mode requires an additional parameter called an IV (initialization vector).
The IV is always 1 block long regardless of the key size.

CBC works like this:
cipher1 = encrypt(key,plain1 ^ IV)
cipher2 = encrypt(key,plain2 ^ cipher1)
cipher3 = encrypt(key,plain3 ^ cipher2)
...
cipherN = encrypt(key,plainN ^ cipherN-1)

Since every block (expect for the first one) uses the output of the previous block, cipherN depends on every plain-text block that came before it as well as the IV. This means that two inputs will only get identical outputs for as long as they are identical, after the first deviation they will look completely different (doesn't matter if they re-converge later).

However from a cracking perspective, this scheme isn't really harder to deal with than ECB.
The decryption pattern looks like this:
plain1 = decrypt(key,cipher1) ^ IV
plain2 = decrypt(key,cipher2) ^ cipher1
plain3 = decrypt(key,cipher3) ^ cipher2
...
plainN = decrypt(key,cipherN) ^ cipherN-1

Since you have access to all the cipher blocks, the chained nature of the algorithm doesn't really complicate your computations.
A happy little fact of life is that if you use the wrong IV only the first block will be incorrect. This means you can hunt for the key before worrying about the IV.

Once you have the key you can determine the IV as long as you know the first plain-text block of any file. Many file types start with a consistent header that takes up the first block, so in many cases you can deduce the first block by just looking at the extension.
The result you get from your incorrect decryption of cipher1 is:
decrypt(key,cipher1) ^ wrongIV

with an IV of 0, this is just:
decrypt(key,cipher1) = plain1 ^ IV

So just XOR your value with the known plain-text to get:
decrypt(key,cipher1) ^ plain1 = plain1 ^ plain1 ^ IV = 0 ^ IV = IV

Simple.
It's for this reason that the IV is not considered to be a second "key", just a parameter.


AES Level 2:
---------------
So how does the encrypt/decrypt function actually work?

To encrypt/decrypt blocks AES operates in "rounds".
The number of rounds depends on the key size.
128bit/16byte -> 10 rounds
192bit/24byte -> 12 rounds
256bit/32byte -> 14 rounds

Let's call the number of rounds 'X'
Each round uses a 128bit key, also called the "round-key".
At the start of the algorithm, the key gets expanded into X+1 128bit keys.
These keys are also called the "expanded" key which can be viewed as a 176 byte, 208 byte, and 240 byte key respectively. However this expanded key only gets accessed in block sized chunks so I think it's more natural to think of it as a list of X+1 separate keys.
I won't cover the method by which the key gets expanded here.

The pseudo-code for the encrypt function looks like this:

Code:

block = block ^ keys[0]
for i in [1,2,...X-1]:
    // Round i
    block = subBytes(block)
    block = shiftRows(block)
    block = mixColumns(block)
    block = block ^ keys[i]

// Round X which is slightly different
block = subBytes(block)
block = shiftRows(block)
block = block ^ keys[X]

return block


The decryption function looks like:

Code:

block = block ^ keys[X]
for i in [X-1,...2,1]:
    // Round i
    block = inv_shiftRows(block)
    block = inv_subBytes(block)
    block = block ^ keys[i]
    block = inv_mixColumns(block)

// Round X which is slightly different
block = inv_shiftRows(block)
block = inv_subBytes(block)
block = block ^ keys[X]

return block

Note on possible confusion:
At first glance it might look like decryption is not symmetric since the looped code does not read:
Code:

block = block ^ keys[i]
block = inv_mixColumns(block)
block = inv_shiftRows(block)
block = inv_subBytes(block)

but that is just because its still formatted as loop + extra. If you read the operations for encryption backwards you'll see it all matches up.


The sub-operations are stateless and don't depend on the key.
The 16-byte block is viewed as a 4x4 byte matrix and:
subBytes -> Remaps byte values​
shiftRows -> Fucks with each row​
mixColumns -> Fucks with each column​

I won't go into more detail than that on the sub-ops (that would be level 3). Google it if you wish to know more.

Now you might be wondering: That's great and all, but how does this affect my cracking?
Two ways:
1. If your digging through code, it's good to have a general idea of what the AES algorithm looks like so you can recognize it when you encounter it
2. When an AES encryption is taking place, you should be able to find the expanded key in memory. Knowing how to reliably get the base key from the expanded key requires you to understand this.

So, you've found an expanded key in memory, how do you get the base key?
For a normal expanded key, the base-key is just the first X bits where X is the length of the base key. When decryption is performed, the expanded key may be loaded in reverse block order, so you need to grab the last blocks, not the first.

This is all super simple UNLESS the algorithm implements the "equivalent inverse cipher" variant.

In that case the decryption function looks like:
Code:

block = block ^ keys[0]
for i in [1,2,...X-1]:
    // Round i
    block = inv_subBytes(block)
    block = inv_shiftRows(block)
    block = inv_mixColumns(block)
    block = block ^ keys[i]

// Round X
block = inv_subBytes(block)
block = inv_shiftRows(block)
block = block ^ keys[X]

Almost the exact same as the encryption function! Neat!

However to make this work, some adjustments need to be made to the expanded key.
1. The keys are accessed 0->X, so the order of keys needs to be reversed to compensate.​
2. In the repeated round, the XOR operation is moved after the mix-columns step.​
Luckily this sub-op has the property that:​
inv_mixColumns(x ^ y) = inv_mixColumns(x) ^ inv_mixColumns(y)​
So if we pre-apply the inv_mixColumns sub-op to all key values other than the first and last we'll get the same result.​

So to obtain the base key from such an expanded key:
1. Reverse the block order​
2. Perform mixColumns() on all but the first and last key​
(Find an AES implementation that lets you perform the sub-ops manually. If you're feeling adventurous you could also write your own.)​
3. Read the first Y bits (where Y = key length)​

Note:
If you're dealing with a 128bit key, it's just the last block in the expanded key. Don't even need a program for that one.

This process can be further complicated if the algorithm uses a different representation for the 4x4 abstract matrix.

I think it's most common that for a block with the bytes x0, x1, x2, ... the 4x4 matrix is:
x0 x1 x2 x3
x4 ...
x8 ...
x12 ..

But for some the interpretation is:
x0 x4 x8 x12
x1 ...
x2 ...
x3 ...

This changes the result of the mixColumns operation.
If there's a mismatch between the representation used by the target application and the implementation you are using you will need to convert the blocks before and after passing them to the mix-columns function (or modify the mix-column function directly).


Pro tip when dealing with AES
--------------------------------------
There are assembly instructions for doing AES operations.
These instructions start with "660F3". Just ctrl-F that shit and you have a good chance of finding a critical function.


Determining if a file is encrypted
------------------------------------------
"Proper" encryption system will result in output that looks completely random.
Every byte value will have a 1/256 chance of occurring. The byte probability distribution should be completely flat.
This is something you can check with a tool or even just eyeball.
If the data looks random, it's probably encrypted (or compressed).

A simple algorithm you could use to assign a "randomness" score to a sequence is:

Code:

// Initialize with 0's
byte histogram[256];

for byte in data:
    histogram[byte] += 1
   
score = 0
for count in histogram:
    score += (count/len(data) - 1/256)^2

return score

This will result in a score of 0 if the probability distribution if perfectly flat and higher scores the more it deviates from the norm.

Note:
You can only get a good estimate of the probability distribution for large files. Determining if a short sequence of binary data is encrypted is very difficult.


A brief note about brute-forcing
-----------------------------------------
I'd consider brute-forcing to be anything where you systematically try a whole bunch of options to find the solution.
Brute-forcing a problem can be very effective and let you advance quickly. Just do a bit of math so you know which problems are manageable. Systematically trying every possible encryption key will never be feasible if a sane key length is being used. However if you discover that the key has some sort of pattern (maybe it's only ascii encoded lowercase characters) then maybe brute-forcing it is an option. If you know that a key is located somewhere in a file, just try every possible offset. The number of possibilities only grows linearly with the file size.


Tiers of difficulty
----------------------

Tier 0: Games that don't use any form of online verification

It's pretty hard to have a DRM system that does not require an internet connection, so projects under this category are more likely to deal with extracting encrypted assets than removing DRM.
Assuming you have all the files that were present during the game's installation, this type of project is always theoretically crackable. All the information is there, you just need to deal with obfuscation.


Tier 0.5: Games that send web-requests, but the web-requests don't contain vital* data

This could be because the DRM system is kind of dumb, or because the game has optional online features (most games that use the steam API don't really *require* it)
If the remote server does not hold data that you need, then you can cut it out of the equation. Either by having the game contact a fake server you control, tricking the game into thinking an incorrect server response is valid, or bypassing the web-request code entirely.

Although on a fundamental level tier 0.5 is very similar to tier 0, unlike tier 0, tier 0.5 apps usually won't run on their own without valid authorization. So unless you own the app, you have a lot less information to work with.


Tier 1: Games that use online verification upon the initial installation (and the server sends vital data)

There are roughly 3 ways to approach such a project:

1. Replicate the credentials of an authorized user (account sharing basically)​
I wouldn't recommend doing this because it can result it the account being banned (bad for the game donor), and once the account is banned the "crack" is broken as well.​
​
2. Get the server to accept a set of fake credentials. Preferably ones that can be randomly generated. (the keygen approach)​
This approach only works if the people in charge of the security system fucked up somewhere. Can work, but it's not reliable.​
​
3. Pass the authentication using valid credentials and then replicate the game's functions such that it can be run independently.​
Depending on how interwoven the DRM system is with the game's code, the "replicate" step could be quite difficult, but in most cases the DRM system is just a light layer on top.​
With this approach you normally need to decrypt the game's files and sometimes replace the .exe used to launch the project.​
For a lot of game engines, the .exe is fairly interchangeable so it's just a case of decrypting the files.​

This approach is the most reliable and should always be theoretically possible.​
But it does require you to possess valid credentials, which normally means buying the game.​


Tier 2: Games that send continuous web-requests that contain vital data.

Multiplayer games fall under this category. If a game uses multiplayer interactions as a primary source of content it would take an enormous amount of effort to crack since you'd have to replicate all undocumented server functions and host your own servers for people to use. For most intents and purposes I'd consider these to be uncrackable.

If a game is single-player but is hosted online, the difficulty depends on how complex the game is.
For example, if it's just a collection of static web pages, then iterating over all of them and storing the data offline should be feasible. Same deal if the webpages just run client-side scripts. If the game relies on a lot of server-side scripts then you have a problem. You can only observe the inputs and outputs from the server and thus can only guess at what the inner mechanics are.


*By "vital data" I mean data that is necessary for the game experience and can't be easily guessed/replicated
This could be an encryption key or just part of the game's content, like chapters or CG images.


General Approaches: Replication vs Zombie Processes
---------------------------------------------------------------------
There are roughly two approaches to cracking problems:
1. Remove the security system and replicate any necessary behaviors​
2. Trick the security system into doing what you want​

For most situations I would highly recommend the second approach because it is normally way easier than reverse engineering the underlying logic. In the case of decryption, you don't need to know what the encryption method is or what the keys are.

The advantages of replicating behavior is:
- Once setup, you don't have to work around the behaviors of the security system​
- It is more simple and elegant solution since you are only performing the necessary operations​
- You learn way more about how the system works, which is good because:​
- You may identify weaknesses you would have otherwise missed​
- Learning can be inherently enjoyable and makes future projects easier​

Miscellaneous Stuff
------------------------

Super Hidden Files
------------------------
You're (hopefully) aware of hidden files and how to show those.
What you might not be aware of is "system files" which require a second option to show. To show system files, go into a folders "View" options and uncheck "Hide protected operating system files". You should now see "pagefile.sys" on your C drive for example.
These files are hidden for a reason though. If you're not actively working on something that requires you to see them I'd recommend keeping them hidden so you don't accidentally delete something.


Manually editing .exe & .dll files
----------------------------------------
Under normal circumstances string constants used by .exe's and .dll's will be stored somewhere in memory. You can often replace these constants with a different string of equal length without breaking the program.

Example 1:
In a real recent example a program was contacting a DRM server to verify ownership. The server URL was stored in the exe. Using a hex editor I was able to change it to instead contact a localhost server I had control over. A quick, dirty, and simple way to perform request redirection.

Example 2:
Let's say you found a string in the exe/dll that looks like it could be a decryption key.
You could try changing it and seeing if the encryption breaks.
If the program breaks it could be for a lot of reasons, but if it doesn't immediately break you can rule that string out as an encryption key. (unless the key is present in multiple locations)

Note:
Programs often perform some sort of integrity check of used files which makes manual edits more difficult.
Which brings me to the next point


Bypassing file integrity checks
---------------------------------------
In some situations if you know *when* a file integrity check is going to take place, you can hook the file-open method and redirect it to an unmodified file that passes the check.


Extended debugging tool check
----------------------------------------
I've encountered one situation where a program would not run because it detected a debugging tool active (process monitor). I was able to get around that by just renaming the debugging program's exe to something else.


Disassembling Unmanaged Code
-----------------------------------------
There are tools for disassembling unmanaged code back into C but I wouldn't recommend using them. All the times I tried disassembling unmanaged code the result was too unwieldy to be of any use. You'll probably get a 20k line file full of functions with 10-20 arguments (everything unnamed of course) and every variable performs a reinterpret_cast every other line.
You're much better off just looking at the assembly. That way you can also observe the code in action.



Getting started
-------------------

For getting started there are roughly two options:

1. Original Work
---------------------
1a) The illegal way​
Look through the cracking forum for a post that interests you and has the uncracked files uploaded. (or buy the game yourself)​
Download the files and start seeing what you can figure out!​
​
1b) The legal way​
Ask a developer if you can do penetration testing on their project. Once you get good you may be able to charge money for this, but to start out with I'd offer to do it for free for the sake of getting experience. Part of this deal is that once the project is done you WONT release anything publicly and instead just report your findings to the dev with tips on how they can make it more secure.​
The developer may not trust you with their game files and say no, but that is the price of taking the high road. Just keep at it.​

The advantage of doing completely original work is that it's the real deal. You won't find any solutions online that tell you how to solve this specific case. It's just you and your wits against the program. It's very satisfying if you're able to make progress knowing that you've broken new ground so to speak.

The disadvantage of doing original work as a beginner is that you have no idea how difficult it is going to be. You could get lucky and get something simple, or you could stumble across something completely outside of your skill range.
Even if the project is outside of your skill level, you should still be able to make some progress and at least learn more about how the system works and learn new skills in the process. But it is more fun when you can make some major strides it breaking the security.


2. Redoing cracked projects
-----------------------------------
If you just want to learn, I can recommend you some projects which I have already cracked. That way I have an idea of how difficult it will be and can give you something simple to start out with. I can also give you some hints on those projects if you get stuck.

The obvious advantage of this is that you'll get manageable tasks to deal with and have some support if you need it.
The drawback is that it's less satisfying to defeat something when you had outside help and know it doesn't contribute anything to our lovely community. Also since it's already cracked you might stumble across an exact solution that spoils the problem.

If you're interested I can dig up some project files from my PC and upload them.
Alternatively, some projects you could try which are currently publicly available:

- White Wings (the uncracked files should still be available)
This is a project I did recently.
It can be cracked without owning or having access to any of the uncracked files.
It has multiple layers of protection which makes it quite interesting to examine.

- The DLSite DRM systems
DLSite actually uses a few different systems. The most common one involves a login prompt when you first boot up the game and is characterized by a file called startup.exe and a bunch of dll files with a "ct" prefix.
As one of my first major projects I made a tool that can remove the DRM protection for games you own. Figure out how I did it or find an alternative way to accomplish the same result.
(Note: This will require you to purchase at least one dlsite game with this protection. The cheapest such game I am aware of is RE141151 for $3)

For the other DLSite DRM systems, some are easy to crack, some are hard. I think the serial-code one may even be uncracked at this point? Not sure.


Conclusion
--------------
That's all I have to say on this topic.
Reading this guide may be like cheating in some ways. I had to figure this stuff out the hard way and here I am just giving you the answers. That said, most of this information is scattered on the web. I just collected it in one place.

I've found one difficulty with cracking is that while there is a lot of information on security systems out there, little of it is written for the perspective of an attacker, so hopefully this guide helps.

Let me know what you think in the comments and whether there's an area you'd like extra information on.
