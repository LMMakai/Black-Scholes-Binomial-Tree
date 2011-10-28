#include <iostream>
using namespace std;
#include <cmath>
#include "makai_qfin.h"


int main()
{
  double NPVholder, vegaoutput, deltaoutput, binomialtreevega, binomialtreepriceoutput, hbinomialtreepriceoutput, binomialtreedeltaoutput, addingitup=0;
	double NPV(int payments, double rf);
	int i, count=1, newdummy;
	CRR_Price tree, htree;
	Black_Scholes price;

	cout << "Enter the current stock price: "; 
	cin >> tree.St;
	cout << "Enter the strike price: ";
    cin >> tree.X;
	cout << "Enter the interest rate: ";
    cin >> tree.rf;
	cout << "Enter the volatility: ";
    cin >> tree.SD;
	cout << "Enter the time to maturity: ";
    cin >> tree.yr;
	cout << "Enter the number of steps: ";
	cin >> tree.steps;
	cout << "Please choose:\n1. European \n2. American" << '\n';
	cin >> tree.americanoreuropean;
	cout << "Please choose:\n1. Call \n2. Put \n3. Call with Continuous Div \n4. Put with Continuous Div \n5. Call with Discrete Div \n6. Put with Discrete Div" << '\n';
    cin >> tree.choice;
	
	if (tree.choice==3 || tree.choice==4)
	{
		cout << "Enter the continuous rate: ";
		cin >> tree.contrate;
	}
	
	if (tree.choice==5 || tree.choice==6)
	{

	cout << "Enter number of payments (1500 max)";
	cin >> tree.pmtnumber;
	htree.pmtnumber = tree.pmtnumber;
	
	for (i=0; i<tree.pmtnumber; i++)
	{
		cout << "Enter dividend payment #"<< count <<": ";
		cin >> tree.pmtarray[count];
		htree.pmtarray[count] = tree.pmtarray[count];
		cout << "Enter the time of dividend payment #"<< count <<": ";
		cin >> tree.timearray[count];
		htree.timearray[count] = tree.timearray[count];
		count=count+1;
	}
	
	for (i=1; i<tree.pmtnumber+1; i++)
	{
		addingitup=addingitup+NPVarray(tree.pmtarray[i],tree.rf,tree.timearray[i]);
	}
	tree.St=tree.St-addingitup;
	}

	if (tree.americanoreuropean==1)
	{
	price.choice = tree.choice;
	price.St = tree.St;
	price.X = tree.X;
	price.rf = tree.rf;
	price.SD = tree.SD;
	price.yr = tree.yr;
	price.contrate = tree.contrate;

	for (i=0;i<58;i++)
	{
		cout << "-";
	}
	cout << "\n";
	cout << "Black-Scholes Values: \n";
	cout << "Price is ";
	price.bs();
	deltaoutput = price.delta();
	vegaoutput = price.vega();

	cout << "Delta is " << deltaoutput << "\n";
	cout << "Vega is " << vegaoutput << "\n";
	for (i=0;i<58;i++)
	{
		cout << "-";
	}
	cout << "\n";
	}

	binomialtreepriceoutput = tree.binomialtree();
	binomialtreedeltaoutput = tree.binomialtreedelta();

	cout << "Binomial Tree Values:";
	cout << "\n";
	cout << "Price is $" << binomialtreepriceoutput << "\n";
	cout << "Delta is " << binomialtreedeltaoutput << "\n";
	


	htree.choice = tree.choice;
	htree.St = tree.St;
	htree.X = tree.X;
	htree.rf = tree.rf;
	htree.SD = tree.SD + .005;
	htree.yr = tree.yr;
	htree.steps = tree.steps;
	htree.americanoreuropean = tree.americanoreuropean;
	htree.contrate = tree.contrate;
	htree.payments = tree.payments;

	hbinomialtreepriceoutput = htree.binomialtree();

	binomialtreevega = (hbinomialtreepriceoutput - binomialtreepriceoutput)/.005;

	cout << "Vega is " << binomialtreevega << "\n";
	for (i=0;i<58;i++)
	{
		cout << "-";
	}

	char dummy;
	cout << "\n";
	cout <<"Please type any key, then enter to exit the program.\n";
	cin>>dummy;

	return 0;
}