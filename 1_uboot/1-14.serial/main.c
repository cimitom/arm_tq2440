int gboot_main()
{
	unsigned char buff[10];
	int num = 0;
	#ifdef MMU_ON
		mmu_init();
	#endif
	
	led_init();
	
	button_init();
	
	irq_init();
	
	uart_init();
	
	while(1)
	{
		printf("\n****************************************\n\r");
		printf("\n*****************GBOOT******************\n\r");
		printf("1:Download Linux Kernel from TFTP Server!\n\r");
		printf("2:Boot Linux from RAM !\n\r");
		printf("3:Boot Linux from Nand Flash !\n\r");
		printf("\nPlease Select : ");
		
		scanf("%d", &num);
		
		switch (num)
		{
			case 1:
				printf("selected 1 !\n\r");
				break;
			case 2:
				printf("selected 2 !\n\r");
				break;
			case 3:
				printf("selected 3 !\n\r");
				break;
			default:
				printf("Error : This is a wrong slection !\n\r");
				break;
		}
	}
	

	
	return 0;
}
