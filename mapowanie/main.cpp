#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

vector <int> A;
int fragmenty;
int pierwsza;
int maxind;
clock_t start,koniec;
double czas;

void szukaj(int *rozwiazanie,int ind,int *jest)
{
    int i,j,k,l,element,warunek=0;

	int *wykorzystane=new int[A.size()];
	for(i=0;i<A.size();i++)
		wykorzystane[i]=0;

	for(i=0;i<fragmenty;i++)
	{
		for(j=0;j<A.size();j++)
		{
			if(A[j]==rozwiazanie[i])
			{
				if(wykorzystane[j]==0)
				{
					wykorzystane[j]=1;
					break;
				}
			}
		}
	}

	if(ind==maxind)
	{
		int poprawne=1;
		vector<int> sumy;

		for(i=0;i<fragmenty;i++)
		{
			int tmp=rozwiazanie[i];
			sumy.push_back(tmp);
			for(j=i+1;j<fragmenty;j++)
			{
				int suma=tmp+rozwiazanie[j];
				tmp+=rozwiazanie[j];
				sumy.push_back(suma);
			}
		}

		sort(sumy.begin(),sumy.end());
		sort(A.begin(),A.end());

		if(sumy.size()!=A.size())
			poprawne=0;
		else
		{
		    if(sumy.size()==A.size())
            {
                for(i=0;i<sumy.size();i++)
                {
                    if(sumy[i]!=A[i])
                    {
                        poprawne=0;
                        break;
                    }
                }
            }
		}

		if(poprawne)
		{
			for(i=0;i<fragmenty;i++)
				cout<<rozwiazanie[i]<<" ";
            cout<<endl;
			*jest=1;
		}
		else
		{
			int dodatkowa=rozwiazanie[ind];
			for(i=0;i<A.size();i++)
			{
				if(dodatkowa==A[i])
				{
					rozwiazanie[ind]=0;
					wykorzystane[i]=0;
					break;
				}
			}
		}
	}
	if(ind<maxind)
	{
        for(i=0;i<A.size();i++)
        {
            int dalej=1;
            if (wykorzystane[i]==0)
            {
                element=A[i];
                rozwiazanie[ind+1]=element;

                for(j=0;j<maxind;j++)
                {
                    int sklad=rozwiazanie[j];
                    for(k=j+1;k<fragmenty;k++)
                    {
                        int suma=sklad+rozwiazanie[k];
                        sklad+=rozwiazanie[k];
                        warunek=0;

                        if(suma==0)
                            warunek=1;
                        else
                        {
                            for(l=0;l<A.size();l++)
                            {
                                if(suma==A[l])
                                    warunek=1;
                            }
                        }
                        if(warunek==0)
                        {
                            dalej=0;
                            rozwiazanie[ind+1]=0;
                            break;
                        }
                        else
                            dalej=1;
                    }
                    if(warunek==0)
                        break;
                }
                if(dalej)
                    szukaj(rozwiazanie,ind+1,jest);
            }
            if(*jest==1)
                break;
        }
	}
}

int main()
{
    int i,k,ile,licznosc,maks1,maks2,element,pierwsza,tmp;
    ile=0;

    ifstream odczyt("2.5 ciec.txt");
	if(odczyt.is_open())
	{
		while(odczyt>>tmp)
        {
            A.push_back(tmp);
            ile++;
        }
	}
	else
		cout<<"Blad\n";
    odczyt.close();

    for(k=1;k<=ile;k++)
    {
        licznosc=(k+2)*(k+1)/2;
        if(licznosc==ile)
            break;
        else if(licznosc>ile)
            cout<<"Zla licznosc multizbioru"<<endl;
    }
    maks1=maks2=0;

    for(i=0;i<A.size();i++)
    {
        if(A[i]>maks1)
        {
            maks1=A[i];
            element=i;
        }
    }
    if(element==0)
        maks2=A[1];
    else if(element>0)
    {
        element=element-1;
        maks2=A[element];
    }
    pierwsza=maks1-maks2;

    int jest=0;
    fragmenty=k+1;
    maxind=k;

    //sort(A.begin(),A.end());

	int *rozwiazanie=new int[fragmenty];
	for(i=0;i<fragmenty;i++)
		rozwiazanie[i]=0;
    rozwiazanie[0]=pierwsza;

	start=clock();
    szukaj(rozwiazanie,0,&jest);
    koniec=clock();
    czas=(double)(koniec-start)/(double)(CLOCKS_PER_SEC);
	cout<<"\nWykonano w: "<<czas<<" sekund\n"<<endl;

    if(jest==0)
        cout<<"Brak rozwiazania\n";

    delete [] rozwiazanie;

    return 0;
}
