void kernel_entry(unsigned long magic, unsigned long addr) {
}

void die() {
	//Clear hardware interrupts (to prevent the next instruction being interrupted) and then "hlt".
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
	//If that fails, busy loop.
	LOOP: goto LOOP;
}
