#include <bits/stdc++.h>
using namespace std;

int problem_size;
long long number_of_evaluations;
int random_seed;
int kth_bisection;
bool crossover_option;
bool problem_option;

struct individual
{
	bool *value = new bool[problem_size];
	int *fitness = new int;
};

individual *population;
individual *parent;
individual *offspring;
individual *pool;

void freeupspace(individual *a, int n)
{
    for(int i = 0; i < n; i++)
    {
        delete[] a[i].value;
        delete a[i].fitness;
    }
    delete[] a;
}

int countBit(bool *v)
{
    int c = 0;
    for(int i = 0; i < problem_size; i++)
    {
        if (v[i]) c++;
    }
    return c;
}

int onemaxFitness(individual temp)
{
	number_of_evaluations++;
	return countBit(temp.value);
}

int trap5Evaluation(individual temp, int b, int e)
{
	int f_trap = 0;
	for(int i = b; i < e; i++)
	{
		if(temp.value[i]) f_trap++;
	}
	if (f_trap == 5) return 5;
	return 4 - f_trap;
}

int trap5Fitness(individual temp)
{
	number_of_evaluations++;
	int f = 0;
	for(int i = 0; i < problem_size; i += 5)
	{
		f += trap5Evaluation(temp, i, i + 5);
	}
	return f;
}

void initializePopulation(int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < problem_size; j++)
		{
			population[i].value[j] = rand()%2;
		}
		*population[i].fitness = (!problem_option) ? onemaxFitness(population[i]) : trap5Fitness(population[i]);
	}
}

void assignValue(bool *a, bool *b)
{
    for(int i = 0; i < problem_size; i++)
    {
        a[i] = b[i];
    }
}

void assignPopulation(individual *a, individual *b, int n)
{
    for(int i = 0; i < n; i++)
    {
        assignValue(a[i].value, b[i].value);
        *a[i].fitness = *b[i].fitness;
    }
}

void crossover1X(bool *a, bool *b)
{
	int index = rand() % problem_size;
	for(int i = index; i < problem_size; i++)
	{
		swap(a[i], b[i]);
	}
}

void crossoverUX(bool *a, bool *b)
{
	for(int i = 0; i < problem_size; i++)
	{
	    double t = (double)rand() / (RAND_MAX);
		if ((t) < 0.5)
			swap(a[i], b[i]);
	}
}

void generateOffspring1X(int n)
{
	for(int i = 0; i < n; i += 2)
	{
		crossover1X(offspring[i].value, offspring[i + 1].value);
		*offspring[i].fitness = (!problem_option) ? onemaxFitness(offspring[i]) : trap5Fitness(offspring[i]);
		*offspring[i + 1].fitness = (!problem_option) ? onemaxFitness(offspring[i + 1]) : trap5Fitness(offspring[i + 1]);
	}
}

void generateOffspringUX(int n)
{
	for(int i = 0; i < n; i += 2)
	{
		crossoverUX(offspring[i].value, offspring[i + 1].value);
		*offspring[i].fitness = (!problem_option) ? onemaxFitness(offspring[i]) : trap5Fitness(offspring[i]);
		*offspring[i + 1].fitness = (!problem_option) ? onemaxFitness(offspring[i + 1]) : trap5Fitness(offspring[i + 1]);
	}
}

void generateOffspring(int n)
{
    assignPopulation(parent, population, n);
    assignPopulation(offspring, population, n);
	if (!crossover_option) generateOffspring1X(n);
	else generateOffspringUX(n);
}

void generatePool(int n)
{
	for(int i = 0; i < n; i++)
    {
        assignValue(pool[i].value, parent[i].value);
        *pool[i].fitness = *parent[i].fitness;
        assignValue(pool[n + i].value, offspring[i].value);
        *pool[n + i].fitness = *offspring[i].fitness;
    }
}

void shufflePool(int n)
{
    for(int i = 0; i < n; i++)
	{
		swap(pool[rand()%(2*n)], pool[rand()%(2*n)]);
	}
}

individual tournament(int b, int e)
{
	int max_fitness = *pool[b].fitness;
	int max_index = b;
	for(int i = b + 1; i < e; i++)
	{
		if (*pool[i].fitness > max_fitness)
		{
			max_fitness = *pool[i].fitness;
			max_index = i;
		}
	}
	return pool[max_index];
}

void generateNewPopulation(int n)
{
	generatePool(n);
	int index = 0;

    shufflePool(n);
	for(int i = 0; i < 2*n; i += 4)
	{
	    individual temp = tournament(i, i + 4);
		assignValue(population[index].value, temp.value);
		*population[index].fitness = *temp.fitness;
		index++;
	}

	shufflePool(n);
	for(int i = 0; i < 2*n; i += 4)
	{
        individual temp = tournament(i, i + 4);
		assignValue(population[index].value, temp.value);
		*population[index].fitness = *temp.fitness;
		index++;
	}
}

bool checkConvergence(int n)
{
	for(int i = 0; i < n - 1; i++)
	{
	    for(int j = 0; j < problem_size; j++)
		{
		    if (*(population[i].value + j) != *(population[i + 1].value + j)) return false;
		}
	}
	return true;
}

bool checkSolution(int n)
{
	for(int i = 0; i < n; i++)
	{
		if (*population[i].fitness == problem_size)
        {
            freeupspace(population, n);
			return true;
        }
	}
	freeupspace(population, n);
	return false;
}

bool sGA(int n, int random_seed)
{
    srand(random_seed);
    population = new individual[n];
    offspring = new individual[n];
    parent = new individual[n];
    pool = new individual[2*n];
	initializePopulation(n);
	while(true)
	{
		generateOffspring(n);
		generateNewPopulation(n);
		if (checkConvergence(n)) break;
	}
	freeupspace(offspring, n);
	freeupspace(parent, n);
	freeupspace(pool, 2*n);
	return checkSolution(n);
}

bool check(int n)
{
	random_seed = 18520173 + kth_bisection * 10;
	for(int i = 0; i < 10; i++)
	{
		if (!sGA(n, random_seed + i))
			return false;
	}
	return true;
}

int bisection(int problem_size)
{
	int n_upper = 4;
	bool success = false;
	do
	{
		if (n_upper == 8192)
        {
            return 0;
        }
        n_upper = n_upper * 2;
		success = check(n_upper);
	} while (!success);
	int n_lower = n_upper / 2;
	while ((n_upper - n_lower)/double(n_upper) > 0.1)
	{
		int n = (n_upper + n_lower) / 2;
		success = check(n);

		if (success)
		{
			n_upper = n;
		}
		else n_lower = n;

		if (n_upper - n_lower <= 2) break;
	}
	number_of_evaluations = 0;
	check(n_upper);
	return n_upper;
}

double stdDeviation(vector<double> v, double mean)
{
    double deviation = 0;
    for(int i = 0; i < v.size(); i++)
    {
        deviation += pow(v[i] - mean, 2);
    }
    return sqrt(deviation/v.size());
}

int main()
{
    cout << "Problem size: ";
	cin >> problem_size;
	cout << "Onemax or trap? (0: onemax, 1: trap5): ";
	cin >> problem_option;
	cout << "1X or UX crossover? (0: 1X, 1: UX): ";
	cin >> crossover_option;
	vector<double> MRPS;
	vector<double> no_of_evaluation;
	vector<int> random_seed_set;
	double mean_of_no_evaluations = 0;
	double mean_of_MRPS = 0;
	for(kth_bisection = 0; kth_bisection < 10; kth_bisection++)
    {
        cout<<kth_bisection<<endl;
        int n = bisection(problem_size);
        mean_of_MRPS += n;
        mean_of_no_evaluations += ((n == 0) ? 0 : number_of_evaluations/10.0);
        MRPS.push_back(double(n));
        no_of_evaluation.push_back((n == 0) ? 0 : number_of_evaluations/10.0);
        random_seed_set.push_back(random_seed);
    }
	for(int i = 0; i < 10; i++)
    {
        cout<<MRPS[i]<<' '<<no_of_evaluation[i]<<' '<<random_seed_set[i]<<endl;
    }
    cout<<mean_of_MRPS/(10.0)<<' '<<stdDeviation(MRPS, mean_of_MRPS/10.0)<<endl;
    cout<<(mean_of_no_evaluations/(10.0))<<' '<<stdDeviation(no_of_evaluation, mean_of_no_evaluations/10.0)<<endl;
}
