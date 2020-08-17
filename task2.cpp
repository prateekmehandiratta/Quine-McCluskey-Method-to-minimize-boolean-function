#include <bits/stdc++.h>
using namespace std;

typedef struct implicant
{
    int* array;
    int size;
    implicant(int _size)
    {
        size = _size;
        array = new int[size];
    }
    implicant(int _size,implicant i1,implicant i2)
    {
        size = _size;
        array = new int[size];
        for(int i=0;i<size;i++)
        {
            if(i<i1.size)
                array[i] = i1.array[i];
            else
            {
                int skip = i1.size;
                array[i] = i2.array[i-skip];
            }
        }
        sort(array,array+size);
    }
}implicant;

typedef struct Bucket
{
    list<implicant> implicants;
}Bucket;

int numberof1(int v)
{
    int c;
    for(c=0;v;v >>= 1)
        c += v & 1;
    return c;
}

bool compareimplicants(implicant i1,implicant i2)
 {
     int r1=i1.size;
     int r2=i2.size;
     if(r1!=r2)
        return false;
     for(int r=0;r<r1;r++)
     {
         if(i1.array[r1]!=i2.array[r2])
            return false;
     }
     return true;
 }

bool diffofpower2(implicant x,implicant y)
{
    int r1 = x.size;
    int r2 = y.size;
    int diff = y.array[0] - x.array[0];
    if(diff<0)
        return false;
    int c = log2(diff);
    int d = ceil(log2(diff));
    if(c!=d)
        return false;
    for(int i=0;i<r1;i++)
    {
        int temp = y.array[i] - x.array[i];
        if(temp!=diff)
            return false;
    }
    return true;
}

bool isSuperset(implicant newi,implicant old)
{
    int r1 = newi.size;
    int r2 = old.size;
    int check = 0;
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<r2;j++)
        {
            if(newi.array[i] == old.array[j])
                check++;
        }
    }
    if(check == r1)
        return true;
    else
        return false;
}

int main()
{
    stack<Bucket*> store;
    FILE* fp;
    char c;
    fp = fopen("prateek1.txt","r");
    fseek(fp,8,1);
    int count_minterm = 0;
    while((c=getc(fp))!='\n')
    {
        if(c == ' ')
        {
            char x = getc(fp);
            if(x!='\n')
            {
                ++count_minterm;
            }
            fseek(fp,-1,1);
        }
    }
    cout << "No. of input minterms: " << count_minterm << endl;
    rewind(fp);
    fseek(fp,9,1);
    list<int> minterms;
    for(int i=0;i<count_minterm;i++)
    {
        int temp;
        fscanf(fp,"%d",&temp);
        minterms.push_back(temp);
    }
    fclose(fp);
    cout << "Size of minterms list: " << minterms.size() << endl;
    list<int>::iterator ts = minterms.begin();
    list<int>::iterator te = minterms.end();
    cout << "Entries of minterms: ";
    while(ts!=te)
    {
        cout << *ts << " ";
        ++ts;
    }
    int largest_minterm = 0;
    ts = minterms.begin();
    while(ts!=te)
    {
        if(*ts > largest_minterm)
            largest_minterm = *ts;
        ts++;
    }
    cout << "\nLargest entry of minterm: " << largest_minterm << endl;
    int size_of_bucket = ceil(log2(largest_minterm+1));
    cout << "Size of initial p bucket: " << size_of_bucket+1 << "\n" << endl;
    Bucket* pbucket = new Bucket[size_of_bucket+1];
    int no_of_bits = size_of_bucket;
    int minterm[count_minterm];
    ts = minterms.begin();
    for(int i=0;i<count_minterm;i++)
    {
        minterm[i] = *ts;
        ++ts;
    }
    sort(minterm,minterm+count_minterm);
    for(int i=0;i<count_minterm;i++)
    {
        implicant e(1);
        e.array[0] = minterm[i];
        pbucket[numberof1(minterm[i])].implicants.push_back(e);
    }
    for(int i=0;i<size_of_bucket+1;i++)
    {
        if(pbucket[i].implicants.size()!=0)
            store.push(&pbucket[i]);
    }


    while(size_of_bucket>=1)
    {
        Bucket* nbucket = new Bucket[size_of_bucket];
        for(int i=0;i<(size_of_bucket);i++)
        {
            list<implicant>::iterator s1 = pbucket[i].implicants.begin();
            list<implicant>::iterator e1 = pbucket[i].implicants.end();
            while(s1!=e1)
            {
                list<implicant>::iterator s2 = pbucket[i+1].implicants.begin();
                list<implicant>::iterator e2 = pbucket[i+1].implicants.end();
                while(s2!=e2)
                {
                    if(diffofpower2(*s1,*s2))
                    {
                        struct implicant e(2 * ((*s1).size),*s1,*s2);
                        nbucket[i].implicants.push_back(e);
                    }
                    ++s2;
                }
                ++s1;
            }
        }
        for(int i=0;i<(size_of_bucket);i++)
        {
            cout << "nbucket[" << i << "]" << ".......";
            list<implicant>::iterator ns = nbucket[i].implicants.begin();
            list<implicant>::iterator ne = nbucket[i].implicants.end();
            while(ns!=ne)
            {
                cout << "(";
                int arrsize = (*ns).size;
                for(int tr = 0;tr<arrsize;tr++)
                    cout << (*ns).array[tr] << ",";
                cout << ")";
                ns++;
            }
            cout << "\n";
            if(nbucket[i].implicants.size()!=0)
                store.push(&nbucket[i]);
        }
        pbucket = nbucket;
        size_of_bucket--;
    }


    Bucket prime_implicants;
    while(!store.empty())
    {
        Bucket* b = store.top();
        list<implicant>::iterator s1 = (b->implicants).begin();
        list<implicant>::iterator e1 = (b->implicants).end();
        while(s1!=e1)
        {
            int counti=0,check=1;
            list<implicant>::iterator s2 = prime_implicants.implicants.begin();
            list<implicant>::iterator e2 = prime_implicants.implicants.end();
            while(s2!=e2)
            {
                ++counti;
                if(isSuperset(*s1,*s2))
                    check=0;
                s2++;
            }
            if(check == 1)
                prime_implicants.implicants.push_back(*s1);
            s1++;
        }
        store.pop();
    }
    cout << "\nSize of prime implicants bucket: " << prime_implicants.implicants.size() << endl;
    list<implicant>::iterator ps = prime_implicants.implicants.begin();
    list<implicant>::iterator pe = prime_implicants.implicants.end();
    cout << "\nPRIME IMPLICANTS ARE:\n";
    while(ps!=pe)
    {
        int arrsize = (*ps).size;
        cout << "(";
        for(int i=0;i<arrsize;i++)
        {
            cout << (*ps).array[i];
            if(i<(arrsize-1))
            cout << ",";
        }
        cout << ")\n";
        ps++;
    }

    Bucket ess_prime_implicants;
    list<int>::iterator itrs = minterms.begin();
    list<int>::iterator itre = minterms.end();
    while(itrs!=itre)
    {
        implicant e(1);
        e.array[0] = *itrs;
        int count = 0;
        ps = prime_implicants.implicants.begin();
        list<implicant>::iterator temp;
        while(ps!=pe)
        {
            if(isSuperset(e,*ps))
            {
                ++count;
                temp = ps;
            }
            ++ps;
        }
        if(count==1)
        {
            list<implicant>::iterator eps = ess_prime_implicants.implicants.begin();
            list<implicant>::iterator epe = ess_prime_implicants.implicants.end();
            int check = 0;
            while(eps!=epe)
            {
                if(isSuperset(*temp,*eps))
                    check = 1;
                eps++;
            }
            if(check==0)
                ess_prime_implicants.implicants.push_back(*temp);
            int r = (*temp).size;
        }
        itrs++;
    }

    list<implicant>::iterator eps = ess_prime_implicants.implicants.begin();
    list<implicant>::iterator epe = ess_prime_implicants.implicants.end();
    while(eps!=epe)
    {
        ps = prime_implicants.implicants.begin();
        list<implicant>::iterator temp,temp1;
        while(ps!=pe)
        {
            temp1=ps;
            temp=ps;
            ps++;
            if(compareimplicants(*eps,*temp1))
            {
                prime_implicants.implicants.erase(temp);
                break;
            }
        }
        eps++;
    }

    eps = ess_prime_implicants.implicants.begin();
    cout << "\nEssiential prime implicants: \n";
    while(eps!=epe)
    {
        int r = (*eps).size;
        for(int i=0;i<r;i++)
        {
            cout << (*eps).array[i] << " " ;
        }
        cout << "\n";
        eps++;
    }

    list<int> mintermsr;
    ts = minterms.begin();
    while(ts!=te)
    {
        int check = 1;
        eps = ess_prime_implicants.implicants.begin();
        while(eps!=epe)
        {
            int arrsize = (*eps).size;
            for(int z=0;z<arrsize;z++)
            {
                if(*ts == (*eps).array[z])
                    check =0;
            }
            ++eps;
        }
        if(check == 1)
            mintermsr.push_back(*ts);
        ts++;
    }
    cout << "\nNo. of entries remained after epi bucket filling: " << mintermsr.size() << " ";
    list<int>::iterator rs = mintermsr.begin();
    list<int>::iterator re = mintermsr.end();
    cout << "\nMinterm list after epi bucket: ";
    while(rs!=re)
    {
        cout << *rs << " ";
        rs++;
    }
    ps = prime_implicants.implicants.begin();
    cout << "\nSize of remaining pi bucket after epi bucket: " << prime_implicants.implicants.size() << " ";
    int arr[prime_implicants.implicants.size()],index = 0;
    while(ps!=pe)
    {
        int loopsize = (*ps).size;
        int counti = 0;
        for(int g=0;g<loopsize;g++)
        {
            int r = (*ps).array[g];
            rs = mintermsr.begin();
            while(rs!=re)
            {
                if(r == *rs)
                    counti++;
                ++rs;
            }
        }
        arr[index] = counti;
        ++index;
        ps++;
    }
    cout << "\n\nArray values for pi bucket: \n";
    for(int e=0;e<(prime_implicants.implicants.size());e++)
        cout << " " << arr[e] << " ";

    int r = mintermsr.size();
    while(r>0)
    {
        ps = prime_implicants.implicants.begin();
        int max = 0,loc;
        for(int i = 0;i<(prime_implicants.implicants.size());i++)
        {
            if(arr[i]>max)
            {
                max = arr[i];
                loc = i;
            }
        }
        for(int w=0;w<loc;w++)
            ++ps;
        ess_prime_implicants.implicants.push_back(*ps);
        arr[loc] = 0;
        int index=0;
        ps = prime_implicants.implicants.begin();
        while(ps!=pe)
        {
            if(index != loc)
            {
                int arrsize = (*ps).size;
                int count = 0;
                for(int i=0;i<arrsize;i++)
                {
                    rs = mintermsr.begin();
                    while(rs!=re)
                    {
                        if((*ps).array[i] == *rs)
                        {
                            int cond = 1;
                            eps = ess_prime_implicants.implicants.begin();
                            while(eps!=epe)
                            {
                                for(int t=0;t<(*eps).size;t++)
                                {
                                    if((*ps).array[i] == (*eps).array[t])
                                        cond=0;
                                }
                                eps++;
                            }
                            if(cond==1)
                                count++;
                        }
                        rs++;
                    }
                }
                if(arr[index]!=0 && count<arr[index])
                   arr[index] = count;
            }
            index++;
            ps++;
        }
        cout << "\n";
        for(int e=0;e<(prime_implicants.implicants.size());e++)
            cout << " " << arr[e] << " ";
        r -= max;
    }
    cout << "\n\nFINAL IMPLICANTS:\n";
    eps = ess_prime_implicants.implicants.begin();
    while(eps!=epe)
    {
        int arrsize = (*eps).size;
        for(int i=0;i<arrsize;i++)
        {
            cout << (*eps).array[i] << " " ;
        }
        cout << "\n";
        eps++;
    }


    fp = fopen("prateek1.txt","r");
    while((c=getc(fp))!='\n')
        continue;
    fseek(fp,20,1);
    char I[no_of_bits];
    cout << "\nCount of input specification: " << no_of_bits << endl;
    int trav = 0;
    while((c=getc(fp))!='\n')
    {
        if(c!= ' ')
        {
            I[trav] = c;
            trav++;
        }
    }

    eps = ess_prime_implicants.implicants.begin();
    cout << "\n\t\t\t\tFINAL EXPRESSION:\n\t\t\t\t";
    while(eps!=epe)
    {
        int r = (*eps).size;
        for(int i=(no_of_bits-1);i>=0;--i)
        {
            std::bitset<32> bin((*eps).array[0]);
            int check = bin[i],test = 1;
            for(int j=1;j<r;j++)
            {
                std::bitset<32> bin((*eps).array[j]);
                if(bin[i]!=check)
                {
                    test = 0;
                }
            }
            if(test == 0)
                continue;
            if(check == 1)
                cout << I[no_of_bits-i-1];
            else
                cout << I[no_of_bits-i-1] << "'";
        }
        eps++;
        if(eps!=epe)
            cout << " + ";
    }
    cout << "\n";
    return 0;
}
