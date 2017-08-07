#include <iostream>

using namespace std;

long long int gcd(long long int, long long int);
unsigned int depth (long long int, long long int);
int sign(long long int);

int main() {
	long long int A, B, X, Y, D;
	unsigned long long int min, max;
	unsigned int index;
	bool switched;

	cout << endl;
	cout << "=====================================================================||" << endl;
	cout << "Here we will explore the extended Euclidean algorithm." << endl;
	cout << "We will execute this algorithm to find solutions x and y so that" << endl;
	cout << "\t" << "Ax+By = gcd(A,B)" << endl;
	cout << "where A and B are integers." << endl;
	cout << "  Please enter A: ";
	cin >> A;
	while (cin.fail()) {
		cout << "Whoops! Make sure you input an integer." << endl;
		cout << "  Please enter A: ";
		cin.clear();
		cin.ignore();
		cin >> A;
	}

	cout << "  Please enter B: ";
	cin >> B;
	while (cin.fail()) {
		cout << "Whoops! Make sure you input an integer." << endl;
		cout << "  Please enter B: ";
		cin.clear();
		cin.ignore();
		cin >> B;
	}

	D = gcd(sign(A)*A,sign(B)*B);

	cout << endl;
	cout << "Using the standard Euclidean algorithm, we find that" << endl;
	cout << "\t" << "gcd(" << A << "," << B << ") = " << D << "." << endl;
	cout << "Now we will search for x and y so that" << endl;
	cout << "\t" << A << "x+" << B << "y = " << D << "." << endl;
	cout << "=====================================================================||" << endl;

	if (A == 0 and B == 0) {
		X = 0; Y = 0;
		cout << "This is a trivial case and any x and y work." << endl;
		cout << "In particular, a fine solution is" << endl;
		cout << "\t" << "x=0 and y=0." << endl;
	}
	else if (A == 0) {
		X = 0; Y = sign(B);
		cout << "This is a trivial case but we have to pick the right value for y." << endl;
		cout << "Upon inspection, a solution is" << endl;
		cout << "\t" << "x=0 and y=" << Y << "." << endl;
	}
	else if (B == 0) {
		X = sign(A); Y = 0;
		cout << "This is a trivial case but we have to pick the right value for x." << endl;
		cout << "Upon inspection, a solution is" << endl;
		cout << "\t" << "x=" << X << " and y=0." << endl;
	}
	else {
		if (D > 1) {
			cout << "Since " << D << " is a common factor of " << A << " and " << B << "," << endl;
			cout << "we can divide throughout wihout affecting the solutions." << endl;
			cout << "So we now have the equation" << endl;

			A = A/D;		//	Simplifying the
			B = B/D;		//	job a bit

			cout << "\t" << A << "x+" << B << "y = 1." << endl;
		}
		index = depth(sign(A)*A,sign(B)*B);
		long long int D[index+1][2];
		long long int E[index+1][2];
		if (sign(A)*A < sign(B)*B) {
			min = A; max = B;
			switched = true;
		}
		else {
			min = B; max = A;
			switched = false;
		}

		if (switched) {
			cout << "One should note that finding a solution to any Ax+By = gcd(A,B)" << endl;
			cout << "is symmetric in the sense that we can swap A and B. To execute the" << endl;
			cout << "standard Euclidean algorithm, it makes sense to ensure that A is" << endl;
			cout << "larger in absolute value. With this in mind, we will now be solving" << endl;
			cout << "\t" << max << "x+" << min << "y = 1." << endl;
		}

		D[0][0] = max; D[0][1] = min;
		for (unsigned int i = 0; i < index; i++) {
			D[i+1][0] = D[i][1];
			D[i+1][1] = D[i][0]%D[i][1];
			max = D[i][0];
			min = D[i][1];
		}
		D[index][0] = D[index-1][1];
		D[index][1] = 0;

		cout << "First, we record the numbers computed while running the standard" << endl;
		cout << "Euclidean algorithm. The rule here is that A_0 = A, B_0 = B, and" << endl;
		cout << "recursively, A_(i+1) = B_i and B_(i+1) = A_i % B_i." << endl;
		cout << "This algorithm stops when we reach gcd(A,B) which, in this case," << endl;
		cout << "by our choice to reduce A and B to be relatively prime, is when" << endl;
		cout << "we reach 1." << endl << endl;

		for (unsigned int i = 0; i <= index; i++) {
			cout << "\t" << "A_" << i << " = " << D[i][0] << "; " << "B_" << i << " = " << D[i][1] << endl;
		}

		cout << endl;
		cout << "Reaching 1, we start by solving the trivial equation" << endl;
		cout << "\t" << D[index][0] << "x+" << D[index][1] << "y = 1." << endl;

		E[0][0] = sign(D[index][0]);
		E[0][1] = 0;

		cout << "Since we will be tracing backwards, we will want to choose a" << endl;
		cout << "convenient indexing convention. With this in mind, observe" << endl;
		cout << "that a solution, x_" << index << " and y_" << index << ", to" << endl;
		cout << "the equation " << D[index][0] << "x+" << D[index][1] << "y = 1 is" << endl;
		cout << "\t" << "x_" << index << " = " << E[0][0] << " and ";
		cout << "y_" << index << " = " << E[0][1] << "." << endl << endl;

		cout << "To obtain a solution to our original equation, ";
		if (switched) {
			cout << B << "x+" << A << "y = 1," << endl;
		}	else {
			cout << A << "x+" << B << "y = 1," << endl;
		}
		cout << "we will trace back to x_0 and y_0 in the following way." << endl;
		cout << "Given x_i and y_i, we recursively compute x_(i-1) = y_i and" << endl;
		cout << "y_(i-1) = x_i - y_i*floor(A_i / B_i)." << endl << endl;

		for (unsigned int i = 0; i < index; i++) {
			E[i+1][0] = E[i][1];
			E[i+1][1] = E[i][0] - (int)(D[index - (i+1)][0]/D[index - (i+1)][1])*E[i][1];
		}

		for (unsigned int i = 0; i <= index; i++) {
			cout << "\t" << "x_" << index-i << " = " << E[i][0] << "; " << "y_" << index-i << " = " << E[i][1] << endl;
		}

		cout << endl;
		cout << "Finally, our solution is painlessly provided to us:" << endl;
		cout << "\t" << "x_0 = " << E[index][0] << " and " << "y_0 = " << E[index][1] << "." << endl;
		cout << "That is," << endl;
		if (switched) {
			cout << "\t" << B << "*(" << E[index][0] << ") + " << A << "*(" << E[index][1] << ") = 1." << endl;
		}	else {
			cout << "\t" << A << "*(" << E[index][0] << ") + " << B << "*(" << E[index][1] << ") = 1." << endl;
		}


	}

	cout << endl;

	return 0;
}

long long int gcd(long long int x, long long int y) {
	if (y < x) {
		long long int t = x; x = y; y = t; //	Swapping x and y
	}
	if (x == 0) {
		x = y;
	} else {
		while (y%x != 0) {
			long long int t = y;
			y = x;
			x = t%x;
		}
	}

	return x;
}

unsigned int depth (long long int x, long long int y) {
	unsigned int count = 1;

	if (y < x) {
		long long int t = x; x = y; y = t; //	Swapping x and y
	}
	if (x != 0) {
		while (y%x != 0) {
			count++;
			long long int t = y;
			y = x;
			x = t%x;
		}
	}

	return count;
}

int sign(long long int x) {
	int s;
	if (x < 0) {
		s = -1;
	} else if (x == 0) {
		s = 0;
	} else {
		s = 1;
	}

	return s;
}
