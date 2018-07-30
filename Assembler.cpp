#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "function.cpp"


using namespace std;

string find_jump(string jmp){
	switch(jmp[1])
	{
		case 'G':
			{
				if(jmp[2]=='E')
					return "011";
				else
					return "001";
			}
		case 'L':
			{
				if(jmp[2]=='E')
					return "110";
				else
					return "100";
			}
		case 'E':
			{
				return "010";
			}
		case 'N':
			{
				return "101";
			}
		case 'M':
			{
				return "111";
			}
		default:
			{
				return "000";
			}
	}
}


int main(){
	ifstream infile;
	infile.open("test_prog.txt");
	//insert type here
	map <string,int> predefined;
	predefined["R0"] = 0;
	predefined["R1"] = 1;
	predefined["R2"] = 2;
	predefined["R3"] = 3;
	predefined["R4"] = 4;
	predefined["R5"] = 5;
	predefined["R6"] = 6;
	predefined["R7"] = 7;
	predefined["R8"] = 8;
	predefined["R9"] = 9;
	predefined["R10"] = 10;
	predefined["R11"] = 11;
	predefined["R12"] = 12;
	predefined["R13"] = 13;
	predefined["R14"] = 14;
	predefined["R15"] = 15;
	predefined["SP"] = 0;
	predefined["LCL"] = 1;
	predefined["ARG"] = 2;
	predefined["THIS"] = 3;
	predefined["THAT"] = 4;
	predefined ["SCREEN"] = 16348;
	predefined ["KBD"] = 24576;
	map <string,string> computation_map;
	computation_map["0"] = "101010";
	computation_map["1"] = "111111";
	computation_map["-1"] = "111010";
	computation_map["D"] = "001100";
	computation_map["A"] = "110000";
	computation_map["M"] = "110000";
	computation_map["!D"] = "001101";
	computation_map["!A"] = "110001";
	computation_map["!M"] = "110001";
	computation_map["-D"] = "001111";
	computation_map["-A"] = "110011";
	computation_map["-M"] = "110011";
	computation_map["D+1"] = "011111";
	computation_map["A+1"] = "110111";
	computation_map["M+1"] = "110111";
	computation_map["D-1"] = "001110";
	computation_map["A-1"] = "110010";
	computation_map["M-1"] = "110010";
	computation_map["D+A"] = "000010";
	computation_map["D+M"] = "000010";
	computation_map["D-A"] = "010011";
	computation_map["D-M"] = "010011";
	computation_map["A-D"] = "000111";
	computation_map["M-D"] = "000111";
	computation_map["D&A"] = "000000";
	computation_map["D&M"] = "000000";
	computation_map["D|A"] = "010101";
	computation_map["D|M"] = "010101";
	if(infile.fail()){
		cout<<"Error Opening File"<<endl;
		exit(1);
	}
	else{
		char c;
		string line;
		int line_number = 0;
		//In the first Iteration we find about variables and loops
		vector <string> var_vector;
		map <string,int> var_map;
		map <string,int> loop_map;
		while(getline(infile,line)){
			//Find Comments if any
			size_t found_comment = line.find("//",0);
			int len = 0;
			if(found_comment!=0)
			{
				line = line.substr(0,found_comment-1);
				len = line.length();
			} 	
			if(len!=0)
			{
				size_t found_ainst = line.find('@',0);
				size_t found_loop = line.find('(',0);
				//Check Which type of instruction
				if(found_ainst!=string::npos){
					//A instruction Type
					string var_name,temp;
					temp.append(line,(found_ainst+1),(len-found_ainst-1));
					int end;
					for(end=0;end<temp.length();end++)
						if(temp[end]==32)
							break;
					//Ignore Spaces after the variable name
					var_name.append(temp,0,end);
					if(!((47<var_name[0])&&(var_name[0]<58))){
						//it should be either a variable or a loop
						map <string,int> :: iterator it; 
						it = loop_map.find(var_name);
						if(it==loop_map.end())
							var_vector.push_back(var_name);
					}
				}
				//Now check if a loop was found
				else if(found_loop!=string::npos){
					size_t found_close = line.find(')',0);
					string loop_name = line.substr((found_loop+1),(found_close-1));
					loop_map.insert(pair<string,int>(loop_name,line_number));
//					vector <string> ::iterator it;
//					it = var_vector.find(loop_name);
//					if(it!=var_vector.end()){
//						var_vector.erase(loop_name);
				//	}
				}
				if(found_loop==string::npos)
				{	
						cout<<"Line:"<<line_number<<' ';
						cout<<line<<endl;
						line_number++;
				}
		    }
		}
		vector <string> :: iterator it;
		int var_assign = 16;
		cout<<"Variables are:"<<endl;
		//var_map.insert(pair<string,int>(var_name,-1));
		for(it=var_vector.begin();it!=var_vector.end();it++){
			if(loop_map.find(*it)==loop_map.end())
			{
				if(predefined.find(*it)==predefined.end())
				{
					var_map.insert(pair<string,int>(*it,var_assign));
					//it->second = var_assign;
					var_assign++;
				}
				else
				{
					var_map.insert(pair<string,int>(*it,predefined[*it]));
				}
				cout<<*it<<":"<<var_map[*it]<<endl;
			}
			else
				var_vector.erase(it);
		}
		cout<<"Loops are:"<<endl;
		map <string,int> :: iterator itm;
		for(itm=loop_map.begin();itm!=loop_map.end();itm++){
			cout<<itm->first<<":"<<itm->second<<endl;
		}
		infile.close();
		infile.open("test_prog.txt");
		if(infile.fail()){
			cout<<"Error Reopening the File"<<endl;
			exit(1);
		}
		ofstream out_file;
		out_file.open("output_bit.txt");
		if(out_file.fail())
		{
			cout<<"Error Creating a Output File"<<endl;
			exit(1);
		}
		line_number = 0;
		//Now we iterate for the second time
		while(getline(infile,line))
		{
			//Find Comments if any
			size_t found_comment = line.find("//",0);
			if((found_comment-1)>=0)
				line = line.substr(0,found_comment);
			int len = line.length();	
			if(len!=0)
			{
				string bit_value;
				size_t found_ainst = line.find('@',0);
				size_t found_loop = line.find('(',0);
				if(found_loop==string::npos)
				{
					if(found_ainst!=string::npos)
					{
						//A instruction Type
						string var_name;
						var_name.append(line,(found_ainst+1),(len-found_ainst-1));
						int to_convert = 0;
						//Some Variable or loop
						if(!((47<var_name[0])&&(var_name[0]<58))){
							map <string,int> :: iterator it;
							it = var_map.find(var_name);
							if(it!=var_map.end()){
								to_convert = var_map[var_name];
							}
							else{
								to_convert = loop_map[var_name];
							}
						}
						//Some integer value
						else
						{
							string number;
							number.append(line,(found_ainst+1),(len-found_ainst-1));
							int num_length = number.length();
							//To write: Program to ignore spaces
							int i = 0;
							while(i<num_length){
								int v = (int)number[i]%48;
								to_convert = (to_convert*10)+v;
								i++;
							}
						}
						//cout<<"Number decode at line:"<<line_number<<' '<<to_convert<<endl;
						while(to_convert!=0){
							int temp = to_convert%2;
							char c = (char)temp+48;
							//insert at start;
							bit_value.insert(bit_value.begin(),c);
							to_convert /= 2;
						}
						int no_bits = bit_value.size();
						//Append the rest of MSB's with Zeros
						for(int i=1;i<=(16-no_bits);i++)
							bit_value.insert(bit_value.begin(),'0');
						out_file<<bit_value<<endl;
					}
					
					else
					{
						//C instruction
						size_t found_eq = line.find('=');
						size_t found_end = line.find(';');
						
						//***************** Newly Added Code **************************//
						string dest,comp,jump;
						if(found_eq!=string::npos)
							dest = line.substr(0,found_eq);
						else
							dest = '\0';
						if(found_end!=string::npos)
						{
							comp = line.substr(found_eq+1,found_end);
							jump = line.substr(found_end+1,len);
						}
						else{
							comp = line.substr(found_eq+1,len);
							jump = '\0';
						}
			    		//Remove any spaces in the computation string
						int comp_len = comp.length();
						int i = 0;
						string temp;
						while(i!=comp_len)
						{
							if(comp[i]!=' ')
								temp += comp[i];
							i++;
						}
						comp = temp;
				
						//***************************************************************//
						if((found_eq!=string::npos))
						{
							size_t found_D_dest = dest.find('D');
							size_t found_M_dest = dest.find('M');
							size_t found_A_dest = dest.find('A');
							size_t found_M_comp = comp.find('M');
							size_t found_A_comp = comp.find('A');
							if((found_end==string::npos))
							{
								//Then there is a computation part and no jump part
								cout<<"Computation:"<<comp<<endl;
								char* destination = new char[3];
								find_dest(destination,found_D_dest,found_M_dest,found_A_dest);
								string computation = computation_map[comp];
								string to_write = "111";
								if((found_M_comp!=string::npos)&&(found_A_comp==string::npos))
									to_write += '1';
								else
									to_write += '0';
								to_write += computation;
								to_write += destination;
								to_write += "000";
								out_file<<to_write<<endl;
							}
							else
							{
								//Then there is a computation part and a jump part
								jump = line.substr(found_end+1,len-1);
								//Remove any spaces in the computation string
								cout<<"Computation:"<<comp<<endl;
								char* destination = new char[3];
								find_dest(destination,found_D_dest,found_M_dest,found_A_dest);
								string computation = computation_map[comp];
								string to_write = "111";
								if((found_M_comp!=string::npos)&&(found_A_comp==string::npos))
									to_write += '1';
								else
									to_write += '0';
								to_write += computation;
								to_write += destination;
								string j = find_jump(jump);
								to_write += j;
								out_file<<to_write<<endl;
							}
						}
						else if((found_eq==string::npos)&&(found_end!=string::npos))
						{	
							//No destination 
							size_t found_M_comp = comp.find('M');
							size_t found_A_comp = comp.find('A');
							string computation,j;
							computation = computation_map[comp];
							j = find_jump(jump);
							string to_write = "111";
							if((found_M_comp!=string::npos)&&(found_A_comp==string::npos))
								to_write += '1';
							else
								to_write += '0';
							to_write += computation;
							to_write += "000";
							to_write += j;
							out_file<<to_write<<endl;
						}
					}
					line_number++;
				}
		    }
		}
		out_file.close();
		infile.close();
	}
	return 0;
}
