#include<stdio.h>
#include<bits/stdc++.h>
#include<string>
using namespace std;



int power(int a,int b)
{
	int result = 1;
	if(b==0)
		return 1;
	int y = 1;
	while(y<=b)
	{
		result = result * a;
		y++;
	}
	return result;
}



int main()
{
    FILE* fp;
    fp = fopen("prateek.txt","r");




    char c;
    int space=0;
    while((c=getc(fp))== ' ')
    {
        space++;
    }
    fseek(fp,6,1);
    int count_ivar = 0;
	while((c=getc(fp))!='\n')
    {
        if( c != ' ')
            count_ivar++;
    }




    char input_var[count_ivar];
    fseek(fp,space+6,0);
	int i=0;
	while((c=getc(fp))!='\n')
    {
        if( c != ' ')
        {
            input_var[i] = c;
            i++;
        }
    }




    /*i =0;
	cout << count_ivar << endl;
    while(i<count_ivar)
    {
        cout << input_var[i] << endl;
        i++;
    }
    cout << "\n";*/




   	while((c=getc(fp))== ' ')
    {
        continue;
    }
    fseek(fp,7,1);
	int count_ovar = 0;
	while((c=getc(fp))!='\n')
    {
        if(c!=' ')
            count_ovar++;
    }




    char output_var[count_ovar];
	rewind(fp);
	while((c=getc(fp))!='\n')
   	{
        continue;
    }
	while((c=getc(fp))== ' ')
    {
        continue;
    }
    fseek(fp,7,1);
    i = 0;
	while((c=getc(fp))!='\n')
    {
        if(c!=' ')
        {
            output_var[i] = c;
            i++;
        }
    }




	/*cout << count_ovar << endl;
    i =0;
	while(i<count_ovar)
    {
        cout << output_var[i] << endl;
        i++;
    }
    cout << "\n\n\n";*/




    int rows = power(2,count_ivar);
    int table[rows][count_ivar];
    //cout << rows << "\n" << endl;




    for(int i=0;i<rows;i++)
    {
        std::bitset<32> bin(i);
        for(int j=0;j<count_ivar;j++)
        {
            table[i][j] = bin[count_ivar-1-j];
        }
    }




    /*for(int i=0;i<rows;i++)
    {
        for(int j=0;j<count_ivar;j++)
        {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n\n";*/




    string sop[rows];
    string pos[rows];
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<count_ivar;j++)
        {
            if(table[i][j]==0)
            {
                sop[i] += input_var[j] - 32;
                pos[i] += input_var[j];
            }
            if(table[i][j]==1)
            {
                sop[i] += input_var[j];
                pos[i] += input_var[j] -32;
            }
        }
    }




    /*for(int i=0;i<rows;i++)
    {
        cout << sop[i] << endl;
   	}
    cout << "\n\n";

    for(int i=0;i<rows;i++)
    {
        cout << pos[i] << endl;
    }
    cout << "\n\n";*/




	FILE* op;
    op = fopen("output.txt","w");
    putc('.',op);
    putc('i',op);
    putc('n',op);
    putc('p',op);
    putc('u',op);
    putc('t',op);
    putc(' ',op);
	cout << ".input ";




    for(int i=0;i<count_ivar;i++)
    {
        c= input_var[i];
        putc(c,op);
		cout << c << " ";
        putc(' ',op);
    }
    putc('\n',op);
	cout << "\n";




    for(int main=0;main<count_ovar;main++)
    {
		rewind(fp);
        c = output_var[main];
        putc(c,op);
		cout << c;
        for(int j=0;j<(2+main);j++)
        {
            while((c=getc(fp))!='\n')
                continue;
        }
        int countplus =0 ;
        fseek(fp,3,1);




        if((c=getc(fp)) != '(')
        {
			while(fp!=NULL && (c=getc(fp))!='\n')
            {
				if(c == '+')
                {
                    countplus++;
                }
            }
            countplus++;
            //cout << countplus << "\n" << endl;


			putc(' ',op);
			putc('=',op);
			putc(' ',op);
			putc('m',op);
			putc('(',op);
			cout << " = m(";
			rewind(fp);
            for(int j=0;j<(2+main);j++)
            {
                while((c=getc(fp))!='\n')
                    continue;
            }
            fseek(fp,3,1);


            string check[countplus];
            for(int i=0;i<countplus;i++)
            {
                while(fp!= NULL && (c=getc(fp))!=' ')
                {
                    if(c == '\n')
                        break;


                    char x = getc(fp);
                    if(x == '\'')
                    {
                        check[i] += (c - 32);
                    }
                    else
                    {
                        check[i] += c;
                        fseek(fp,-1,1);
                    }

                }
                //cout << check[i] << endl;
                fseek(fp,2,1);
            }
            //cout << "\n";


            for(int j=0;j<rows;j++)
            {
                for(int i=0;i<countplus;i++)
                {
					int test = 0;
                    for(int k=0;k<check[i].size();k++)
                    {
                        for(int h=0;h<sop[j].size();h++)
                        {
                            if(check[i][k] == sop[j][h])
                            {
                                ++test;
                                break;
                            }
                        }
                    }

                    if(test == (check[i].size()))
                    {
                        fprintf(op,"%d",j);
						cout << j << ",";
                        putc(',',op);
                        break;
                    }
                }
            }
            fseek(op,-1,1);
            putc(')',op);
            putc('\n',op);
			cout << ")\n";
        }




		else
        {
            while(fp!=NULL && (c=getc(fp))!='\n')
            {
                if(c == ')')
                {
                    countplus++;
                }
            }
            //cout << countplus << endl;


            putc(' ',op);
            putc('=',op);
            putc(' ',op);
            putc('M',op);
            putc('(',op);
            cout << " = M(";
            fseek(fp,0,0);
            for(int j=0;j<(2+main);j++)
            {
                while((c=getc(fp))!='\n')
                    continue;
            }


            string check[countplus];
            fseek(fp,4,1);
            for(int i=0;i<countplus;i++)
            {
                while(fp!=NULL && (c=getc(fp))!=')')
                {
                    if(c == '+' || c == ' ')
                        continue;
                    char x = getc(fp);
                    if(x == '\'')
                    {
                        check[i] += (c - 32);
                    }
                    else
                    {
                        check[i] += c;
                        fseek(fp,-1,1);
                    }
                }
                fseek(fp,1,1);
                //cout << check[i] << endl;
            }


            for(int j=0;j<rows;j++)
            {
                for(int i=0;i<countplus;i++)
                {
                    int test = 0;
                    for(int k=0;k<check[i].size();k++)
                    {
                        for(int h=0;h<pos[j].size();h++)
                        {
                            if(check[i][k] == pos[j][h])
                            {
                                ++test;
                                break;
                            }
                        }
                    }
                    if(test == (check[i].size()))
                    {
                        fprintf(op,"%d",j);
                        cout << j << ",";
                        putc(',',op);
                        break;
                    }
                }
            }
            fseek(op,-1,1);
            putc(')',op);
            putc('\n',op);
            cout << ")\n";
        }

    }
    fclose(op);
    fclose(fp);
	return 0;
}




