#include <REGX51.H>

unsigned char scan();

#define ssdPORT P1			//SSD connected to PORT1
#define ROWS 		4		//MIN = 1, MAX = 4
#define COLUMNS 	4		//MIN = 1, MAX = 4

//KEYPAD Design Information in terms of SSD sequences (Common Cathode)

//           KEYPAD BUTTONS   |       ARRAY INDEX
//					[1] [2] [3] [ ]	| [ 0] [ 1] [ 2] [ 3]
//					[4] [5] [6] [ ]	| [ 4] [ 5] [ 6] [ 7]
//					[7] [8] [9] [ ]	| [ 8] [ 9] [10] [11]	
//					[ ] [0] [ ] [ ]	| [12] [13] [14] [15]	

//fill this Matrix According to your keypad requirements
unsigned char keypad[ROWS * COLUMNS] = {0x30, 0x6D, 0x79, 0, 
																				 						0x33, 0x5B, 0x5F, 0,
																			   						0x70, 0x7F, 0x7B, 0,
																															  						   0, 0x7E,    0, 0 };

//main program code
void main()
{
	//declare SSD Port as OUTPUT
	ssdPORT = 0;
	
	//get input from keypad
	while(1)
		ssdPORT = keypad[ scan() ];
}

//function for reading the keypad
unsigned char scan()
{
	unsigned char count, pressed, row, column;
	
	//clear counter and flag
	count = 0;
	pressed = 0;
	
	//scan until key press
	while(1)
	for( row=0; row<ROWS; row++ )
	{
		//Select ROW for scanning
		switch( row )
		{
			case 0:
				P2 = 0xEF;		//Load 1110 1111 for scanning 1st row
				break;
			
			case 1:
				P2 = 0xDF;		//Load 1101 1111 for scanning 2nd row
				break;
			
			case 2:
				P2 = 0xBF;		//Load 1011 1111 for scanning 3rd row
				break;
			
			case 3:
				P2 = 0x7F;		//Load 0111 1111 for scanning 4th row
				break;
		}
		
		//COLUMNS scanning
		for( column=0; column<COLUMNS; column++ )
		{
			//Select COLUMN for scanning
			switch( column )
			{
				case 0:
					if( !P2_0 )			//check first column
						pressed = 1;
					break;
				
				case 1:
					if( !P2_1 )			//check second column
						pressed = 1;
					break;
				
				case 2:
					if( !P2_2 )			//check third column
						pressed = 1;
					break;
					
				case 3:
					if( !P2_3 )			//check fourth column
						pressed = 1;
					break;
			}
			
			//check button press flag
			if( pressed )
			return count;
		
			else
			count++;								//increment counter
		}
	}
}
