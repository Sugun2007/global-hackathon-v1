# 🚀 C Data Structures Library (`cdsl`)

> **The plug-and-play toolkit for C learners & builders!**


##  For Linux &  Windows (with WSL2/Ubuntu)

>  **No messy setup. One line to build. Use from anywhere.**  
> Perfect for hackathons, projects, or anyone who hates “it works on my machine” problems!

##  Where to Download Everything
Latest Release (with all ready-to-go resources, Makefile, code, and demo ZIP!)
Download ZIP for version v1.0.0 (download the c-ds-lib zip file)

Check the releases page for a ready-to-use .zip that includes all code, headers, build scripts, and examples—no setup, no hassle!

##  Super-Fast Quick Start

### Linux

<pre>
sudo apt update && sudo apt install build-essential
make
sudo make install</pre>

 Now you can use ds-lib in ALL your C apps!

### Windows (THIS IS COOL — use Ubuntu in WSL2)

- Hit the Windows key, type “powershell”, right-click, run as **Admin**.
<pre>wsl --install
wsl --set-default-version 2
wsl --install -d Ubuntu</pre>


- Open Ubuntu from your Start Menu and run:

<pre>sudo apt update && sudo apt install build-essential git
make
sudo make install</pre>




##  How To Use (It’s SO Easy!)

**In your project’s C code:**  
#include <ds/ds_stack.h>


**To build:**  
<pre>gcc main.c -lds
./a.out</pre>


 **That’s it! No weird flags. No headaches. Data Structures on demand!**



##  Fun Example: Stacks in Two Lines!

<pre>#include <ds/ds_stack.h>
#include <stdio.h>
int main() {
ds_stack_t S = ds_stack_create(); // Make a new stack!
ds_stack_push(S, "🤖"); ds_stack_push(S, "🔥");
printf("%s\n", (char)ds_stack_pop(S)); // 🔥
printf("%s\n", (char*)ds_stack_pop(S)); // 🤖
ds_stack_free(S, NULL);
}</pre>





##  Useful Makefile Commands

| Command                | What it does                                  |
|------------------------|-----------------------------------------------|
| `make`                 | Build the library                             |
| `make demo`            | Try a demo right away                         |
| `make test`            | Build & run included tests                    |
| `sudo make install`    | Installs headers/libs system-wide (*do this!*)|
| `sudo make uninstall`  | Removes from system                           |
| `make clean`           | Wipes build files                             |



##  Troubleshooting (Real Talk)

- **`ds/ds_"data structure".h: No such file...`**  
  👉 Run `sudo make install`, then use `#include <ds/ds_stack.h>`.  
- **`cannot find -lds`**  
  👉 Try `sudo make install` again.
- **Windows**  
  👉 ALWAYS work in the Ubuntu/WSL terminal, never Windows cmd or PowerShell!


## 📦 Folder Tour

- `include/` → All C headers you get after install (`ds.h`, `ds_stack.h`, ...)
- `src/`     → Actual library code
- `tests/`   → Run `make test`!
- `Makefile` → Your new best friend



##  Join the Fun / Contribute

> Hackathons, school, jobs—this makes C easier.
> MIT Licensed, built for the (https://github.com/Sugun2007/global-hackathon-v1)  
> Author: [Sugunadithya Miriampally]  

**Fork, star, or show some love!** 💙

---
