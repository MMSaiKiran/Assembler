//#include <string>

void find_dest(char* temp,size_t D,size_t M,size_t A){
	//char* temp = new char[3];
	if(M!=std::string::npos)
	{
		temp[2] = '1';
	}
	else
	{
		temp[2] = '0';
	}
	if(D!=std::string::npos)
	{
		temp[1] = '1';
	}
	else
	{
		temp[1] = '0';
	}
	if(A!=std::string::npos)
	{
		temp[0] = '1';
	}
	else
	{
		temp[0] = '0';
	}	
	//return temp;
}


char* hex_dec(char c){
	switch(c)
	{
		case '0':
			return "0000";	
		case '1':
			return "0001";
		case '2':
			return "0010";
		case '3':
			return "0011";
		case '4':
			return "0100";
		case '5':
			return "0101";
		case '6':
			return "0110";
		case '7':
			return "0111";
		case '8':
			return "1000";
		case '9':
			return "1001";
		case 'A':
			return "1010";
		case 'B':
			return "1011";
		case 'C':
			return "1100";
		case 'D':
			return "1101";
		case 'E':
			return "1110";
		case 'F':
			return "1111";
	}
}
