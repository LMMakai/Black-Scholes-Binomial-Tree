#include <iostream>
using namespace std;
#include <cmath>

class CRR_Price
{
public:
	int choice, americanoreuropean, payments, pmtnumber;
	double St, X, SD, rf, yr, steps, contrate, pmtarray[1500], timearray[1500];
	double binomialtree(), binomialtreedelta();

private:
};
double CRR_Price::binomialtree()
{
	int i,j,k;
	double up, down, deltatime, p, delta,q, addingitupp=0;
	double NPVarraycurrenttime(double number, double rf, double time, double currenttime);

	deltatime = yr/steps;
	up = exp(SD*sqrt(deltatime));
	down = 1/up;
	p = (exp(rf*deltatime)-down)/(up-down);
	
	if (choice==3 || choice==4)
	{
	q = exp(contrate*deltatime)-1;
	}

	double *anarray = new double[steps+1];

	for (i=0;i<steps+1;i++)
	{
		if (choice==1 || choice==2 || choice==5 || choice==6)
		{
		anarray[i] = St*pow(up,steps-i)*pow(down,i);
		}
		else
		{
		anarray[i] = St*pow(up,steps-i)*pow(down,i)*pow((1-q),steps);
		}
	}

	for (i=0;i<steps+1;i++)
	{
		if (choice==1 || choice==3 || choice==5)
		{
			anarray[i] = anarray[i]-X;
			
			if (anarray[i] < 0)
			{
				anarray[i]=0;
			}
		}
		else
		{
			anarray[i] = X-anarray[i];

			if (anarray[i] < 0)
			{
				anarray[i]=0;
			}
		}
	}

	for (i=steps;i>1;i--)
	{
		for (j=0;j<i;j++)
		{
			anarray[j] = exp(-rf*deltatime)*(p*anarray[j]+(1-p)*anarray[j+1]);

			if (americanoreuropean == 2)
			{

				if (choice==5 || choice==6)
				{
					addingitupp=0;
					for (k=1; k<pmtnumber+1; k++)
					{
					addingitupp=addingitupp+NPVarraycurrenttime(pmtarray[k],rf,timearray[k], deltatime*i);
					}
				
				}

				if (choice==1)
				{
					if (anarray[j] < St*pow(up,i-1-j)*pow(down,j)-X)
					{
						anarray[j] = St*pow(up,i-1-j)*pow(down,j)-X;
					}
				}
				if (choice==2)
				{
					if (anarray[j] < X-St*pow(up,i-1-j)*pow(down,j))
					{
						anarray[j] = X-St*pow(up,i-1-j)*pow(down,j);
					}
				}
				if (choice==3)
				{
					if (anarray[j] < St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1)-X)
					{
						anarray[j] = St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1)-X;
					}
				}
				if (choice==4)
				{
					if (anarray[j] < X-St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1))
					{
						anarray[j] = X-St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1);
					}
				}
				if (choice==5)
				{
					if (anarray[j] < (St*pow(up,i-1-j)*pow(down,j)+addingitupp-X))
					{
						anarray[j] = (St*pow(up,i-1-j)*pow(down,j))+addingitupp-X;
					}
				}
				if (choice==6)
				{
					if (anarray[j] < (X-(St*pow(up,i-1-j)*pow(down,j))-addingitupp))
					{
						anarray[j] = X-(St*pow(up,i-1-j)*pow(down,j))+addingitupp;
					}
				}
			}
		}
	}
	

	delta = (anarray[0]-anarray[1])/(St*(up-down));

	anarray[0] = exp(-rf*deltatime)*(p*anarray[0]+(1-p)*anarray[1]);

	return anarray[0];
}
double CRR_Price::binomialtreedelta()
{
	int i,j,k;
	double up, down, deltatime, p, delta,q, addingitupp=0;
	double NPVarraycurrenttime(double number, double rf, double time, double currenttime);

	deltatime = yr/steps;
	up = exp(SD*sqrt(deltatime));
	down = 1/up;
	p = (exp(rf*deltatime)-down)/(up-down);
	
	if (choice==3 || choice==4)
	{
	q = exp(contrate*deltatime)-1;
	}

	double *anarray = new double[steps+1];

	for (i=0;i<steps+1;i++)
	{
		if (choice==1 || choice==2 || choice==5 || choice==6)
		{
		anarray[i] = St*pow(up,steps-i)*pow(down,i);
		}
		else
		{
		anarray[i] = St*pow(up,steps-i)*pow(down,i)*pow((1-q),steps);
		}
	}

	for (i=0;i<steps+1;i++)
	{
		if (choice==1 || choice==3 || choice==5)
		{
			anarray[i] = anarray[i]-X;
			
			if (anarray[i] < 0)
			{
				anarray[i]=0;
			}
		}
		else
		{
			anarray[i] = X-anarray[i];

			if (anarray[i] < 0)
			{
				anarray[i]=0;
			}
		}
	}

	for (i=steps;i>1;i--)
	{
		for (j=0;j<i;j++)
		{
			anarray[j] = exp(-rf*deltatime)*(p*anarray[j]+(1-p)*anarray[j+1]);

			if (americanoreuropean == 2)
			{

				if (choice==5 || choice==6)
				{
					for (k=1; k<pmtnumber+1; k++)
					{
					addingitupp=addingitupp+NPVarraycurrenttime(pmtarray[k],rf,timearray[k], deltatime*i);
					}
				
				}

				if (choice==1)
				{
					if (anarray[j] < St*pow(up,i-1-j)*pow(down,j)-X)
					{
						anarray[j] = St*pow(up,i-1-j)*pow(down,j)-X;
					}
				}
				if (choice==2)
				{
					if (anarray[j] < X-St*pow(up,i-1-j)*pow(down,j))
					{
						anarray[j] = X-St*pow(up,i-1-j)*pow(down,j);
					}
				}
				if (choice==3)
				{
					if (anarray[j] < St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1)-X)
					{
						anarray[j] = St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1)-X;
					}
				}
				if (choice==4)
				{
					if (anarray[j] < X-St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1))
					{
						anarray[j] = X-St*pow(up,i-1-j)*pow(down,j)*pow((1-q),i-1);
					}
				}
				if (choice==5)
				{
					if (anarray[j] < (St*pow(up,i-1-j)*pow(down,j)+addingitupp-X))
					{
						anarray[j] = (St*pow(up,i-1-j)*pow(down,j))+addingitupp-X;
					}
				}
				if (choice==6)
				{
					if (anarray[j] < X-(St*pow(up,i-1-j)*pow(down,j))-addingitupp)
					{
						anarray[j] = X-(St*pow(up,i-1-j)*pow(down,j))+addingitupp;
					}
				}
			}
			addingitupp=0;
		}
	}
	

	delta = (anarray[0]-anarray[1])/(St*(up-down));

	anarray[0] = exp(-rf*deltatime)*(p*anarray[0]+(1-p)*anarray[1]);

	//cout << "Delta is " << delta << '\n';

	return delta;
}



class Black_Scholes
{
public:

	double newSt, St, X, SD, rf, yr, B, logx, d1, nd1, d2, nd2, callprice, divrate,contrate;
	int i, choice, payments;
	double bs();
	double delta();
	double vega();

private:

};

double Black_Scholes::bs()
{
	double norm(double dinput);
	double NPV(int payments, double rf);

	B= exp(-yr*rf);
	newSt=St;

	if (choice==3 || choice==4)
	{
		divrate=contrate;
		newSt=St/exp(divrate*yr);
	}

	if (choice==1 || choice==3 || choice==5)
	{
	logx= log(newSt/(B*X));
	}
	else if (choice==2 || choice==4 || choice==6)
	{
	logx= log((B*X)/newSt);
	}

	d1= (logx+((SD*SD)/2)*yr)/(SD*sqrt(yr));
	d2= d1-SD*sqrt(yr);	
	nd1= norm(d1);
	nd2= norm(d2);

	if (choice==1)
	{
	callprice= St*nd1 - B*X*nd2;
	}
	else if (choice==2)
	{
	callprice= B*X*nd1 - St*nd2;
	}
	else if (choice==3 || choice==5)
	{
	callprice= newSt*nd1 - B*X*nd2;
	}
	else if (choice==4 || choice==6)
	{
	callprice= B*X*nd1 - newSt*nd2;
	}

	cout <<"$"<< callprice << "\n";
	return 0;
}
double Black_Scholes::delta()
{
	double norm(double dinput);
	double deltad1, deltand1;

	if (choice==3 || choice==4)
	{
		divrate=contrate;
		newSt=St/exp(divrate*yr);
	}

	
	B= exp(-yr*rf);
	logx= log(newSt/(B*X));
	deltad1= (logx+((SD*SD)/2)*yr)/(SD*sqrt(yr));
	
	if (choice==1 || choice==2 || choice==4)
	{
	deltand1= norm(deltad1);
	}
	else
	{
	deltand1= exp(-divrate*yr)*norm(deltad1);
	}
	
	if (choice==2 || choice==6)
	{
	deltand1=(deltand1-1);
	}
	if (choice==4)
	{
	deltand1=exp(-divrate*yr)*(deltand1-1);
	}

	return deltand1;
}
double Black_Scholes::vega()
{
	double nprime, vega, vegaSt;
	const double pi = acos(-1.);

	B = exp(-yr*rf);
	vegaSt = St;

	if (choice==3 || choice==4)
	{
		divrate=contrate;
		vegaSt=St/exp(divrate*yr);
	}

	logx = log(vegaSt/(B*X));
	d1 = (logx+((SD*SD)/2)*yr)/(SD*sqrt(yr));
	nprime = exp(-pow(d1,2)/2)/sqrt(2*pi);
	vega = St*sqrt(yr)*nprime*exp(-divrate*yr);

	return vega;
}
double norm(double dinput)
	{
		double doutput, nprime;
		double k, gamma = .2316419, a1 = .319381530, a2 = -.356563782, a3 = 1.781477937, a4 = -1.821255978, a5 = 1.330274429;
		const double pi = acos(-1.);
		int negg;

		if (dinput < 0) 
		{
			dinput = -dinput;
			negg = 1;
		}
		else
		{
			dinput = dinput;
			negg = 0;
		}

		k= 1/(1+gamma*dinput);

		nprime= exp(-(dinput*dinput)/2)/sqrt(2*pi);

		doutput= 1 - nprime*(a1*k+a2*pow(k,2)+a3*pow(k,3)+a4*pow(k,4)+a5*pow(k,5));

		if (negg == 1) 
		{
			doutput= 1 - doutput;
		}

		return doutput;

	}

double NPV(int payments, double rf)
	{
		int count=1;
		double presentvalue=0, time, pay;

		while (count <= payments)
		{
			cout << "Enter dividend payment #"<< count <<": ";
			cin >> pay;
			cout << "Enter the time of dividend payment #"<< count <<": ";
			cin >> time;
			cout << "\n";
			presentvalue = presentvalue + exp(-rf*time)*pay;

			count = count+1;
			cout << presentvalue;
		}

		return presentvalue;
}


double NPVarray(double number, double rf, double time)
{
	double output;

		output = number*exp(-rf*time);

	return output;
}
double NPVarraycurrenttime(double number, double rf, double time, double currenttime)
{
	double output=0;

	if (currenttime < time)
	{
		output = number*exp(-rf*(time-currenttime));
	}
	return output;
}