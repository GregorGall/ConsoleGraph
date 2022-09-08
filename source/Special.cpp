#include "Special.h"

double minmax(vector<double> In, string type)
{
	double Value = 0;
	for (unsigned int i = 0; i < In.size(); i++) {
		if (isinf(In[i]) == false) { Value = In[i]; break; }
	}
	for (unsigned int i = 0; i < In.size(); i++) {
		if (type == "min") { if (In[i] < Value && isinf(In[i]) == false) { Value = In[i]; }; }
		if (type == "max") { if (In[i] > Value && isinf(In[i]) == false) { Value = In[i]; }; }
	}
	return Value;
}

double sign(double In)
{

	if (In > 0) { return 1; }
	else { if (In < 0) { return -1; }}
	
	return 0.0;
}