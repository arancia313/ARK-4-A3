#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <pspgu.h> // Richiesto da -lpspgu / -lglib2d
#include <stdio.h>
#include <string.h>
#include <intraFont.h>

PSP_MODULE_INFO("sb_forwarder", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

// Semplice configurazione della GPU PSP per pulire lo schermo
void initGraphics() {
    sceGuInit();
    sceGuStart(GU_DIRECT, NULL);
    sceGuDrawBuffer(GU_PSM_8888, (void*)0, 512);
    sceGuDispBuffer(480, 272, (void*)0x88000, 512);
    sceGuClearColor(0xFF000000); // Sfondo nero
    sceGuClearDepth(0);
    sceGuDisplay(GU_TRUE);
    sceGuFinish();
    sceGuSync(0, 0);
}

int main(int argc, char* argv[]) {
    // Inizializza video e font
    initGraphics();
    intraFontInit();
    intraFont* font = intraFontLoad("flash0:/font/ltn0.pgf", INTRAFONT_CACHE_MED);

    // Leggi la modalità
    FILE *f = fopen("ms0:/PSP/SAVEDATA/ARK_30000/CELNUM.TXT", "r");
    int mode = 0;
    if (f != NULL) {
        mode = fgetc(f) - '0';
        fclose(f);
    }

    if (mode == 1) {
        const char* sandbox_root = "ms0:/sandbox";
        const char* boot_log_path = "ms0:/PSP/SAVEDATA/ARK_30000/A3_BOOT.TXT";

        sceIoMkdir(sandbox_root, 0777);

        char target_scratch_file[64];
        int file_found = 0;

        SceUID dfd = sceIoDopen(sandbox_root);
        if (dfd >= 0) {
            SceIoDirent dir;
            while (sceIoDread(dfd, &dir) > 0) {
                char *name = dir.d_name;
                int len = strlen(name);
                if ((len > 4 && strcmp(&name[len - 4], ".sb3") == 0) ||
                    (len > 3 && strcmp(&name[len - 3], ".sb") == 0)) {
                    snprintf(target_scratch_file, sizeof(target_scratch_file), "%s/%s", sandbox_root, name);
                    file_found = 1;
                    break;
                }
            }
            sceIoDclose(dfd);
        }

        if (!file_found) {
            snprintf(target_scratch_file, sizeof(target_scratch_file), "%s/project.sb3", sandbox_root);
        }

        int fd = sceIoOpen(boot_log_path, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
        if (fd >= 0) {
            sceIoWrite(fd, target_scratch_file, strlen(target_scratch_file));
            sceIoClose(fd);
        }
    } else {
        // Ciclo di rendering per mostrare l'errore a schermo per 4 secondi
        int i;
        for(i = 0; i < 240; i++) { // ~4 secondi a 60 FPS
            sceGuStart(GU_DIRECT, NULL);
            sceGuClear(GU_COLOR_BUFFER_BIT);
            
            if (font != NULL) {
                intraFontSetStyle(font, 1.0f, INTRAFONT_COLOR_WHITE, INTRAFONT_COLOR_BLACK, INTRAFONT_ALIGN_LEFT);
                intraFontPrint(font, 20, 136, "Loading is limited to .sb files by default setting.");
                intraFontPrint(font, 20, 156, "You need to edit the celnum.txt file to 1!");
            }
            
            sceGuFinish();
            sceGuSync(0, 0);
            sceDisplayWaitVblankStart(); // Sincronizzazione verticale
        }
    }

    // Pulizia e uscita
    if (font != NULL) intraFontUnload(font);
    intraFontShutdown();
    sceGuTerm();

    sceKernelExitGame();
    return 0;
}
