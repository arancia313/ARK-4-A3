#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("A3_Scratch_Folder_Sandbox", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int main(int argc, char* argv[]) {
    // 1. Definiamo i percorsi fissi in formato stringa
    const char* sandbox_root = "ms0:/sandbox";
    const char* boot_log_path = "ms0:/PSP/SAVEDATA/ARK_30000/A3_BOOT.TXT";

   
    sceIoMkdir(sandbox_root, 0777);

    
    char target_scratch_file[512];
    snprintf(target_scratch_file, sizeof(target_scratch_file), "%s/project.sb3", sandbox_root);

    
    int fd = sceIoOpen(boot_log_path, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (fd >= 0) {
        sceIoWrite(fd, target_scratch_file, strlen(target_scratch_file));
        sceIoClose(fd);
    }


    sceKernelDelayThread(1000000); 

    sceKernelExitGame();
    return 0;
}