struct multiboot_header {

} __attribute__((section(".multiboot")));

int main() {
    char* video_memory = (char*)0xB8000;

    const char* message = "kerneling time";
    
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i * 2] = message[i];
        video_memory[i * 2 + 1] = 0x07;
    }
    
    while(1);
}