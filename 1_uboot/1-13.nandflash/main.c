int gboot_main()
{
	unsigned char buff[10];
	#ifdef MMU_ON
		mmu_init();
	#endif
	
	led_init();
	
	button_init();
	
	irq_init();
	
	led_on();
	
	NF_Erase(64*5);
	
	led_off();
	
/*	buff[0] = 100;
	
	NF_WritePage(0xa0000, buff);
	
	buff[0] = 10;
	
	NF_ReadPage(0xa0000, buff);
	
	if(buff[0] == 10)
	{
		led_off();
	}	
*/	while(1);

	
	return 0;
}
