#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
//#include <iomanip>

std::unordered_map <std::string, double> Genotypes;
std::unordered_map <std::string, double> Phenotypes;

std::string CreateGenotype(std::string father, std::string mother, unsigned NumGenotypes)
{
	std::string Genotype = "";
	std::string Phenotype = "";
	for (size_t i = 0; i < father.length(); i++)
	{
		if (father[i] == tolower(mother[i]))
		{
			Genotype += mother[i];
			Genotype += father[i];
			Phenotype += mother[i];
		}
		else
		{
			Genotype += father[i];
			Genotype += mother[i];
			Phenotype += father[i];
		}
	}
	Phenotypes[Phenotype] += 1.0 / NumGenotypes * 100;
	return Genotype;
}
void PrintGenotypes()
{
	std::ofstream result{ "Genotypes.txt" };
	for (auto& i : Genotypes)
	{
		result /* << std::setprecision(2) << std::fixed*/ << i.first << ": " << i.second << "%" << "\n";
	}
	result.close();
}
void PrintPhenotypes()
{
	std::ofstream result{ "Phenotypes.txt" };
	for (auto& i : Phenotypes)
	{
		result /* << std::setprecision(2) << std::fixed*/ << i.first << ": " << i.second << "%" << "\n";
	}
	result.close();
}
void MakeCombines(unsigned NumGenotypes)
{
	std::ifstream father{ "Father.txt" };
	std::ifstream mother{ "Mother.txt" };
	std::string FatherGamete = "";
	std::string MotherGamete = "";
	father >> FatherGamete;
	size_t i = 0;
	do
	{
		if (mother >> MotherGamete)
		{
			Genotypes[CreateGenotype(FatherGamete, MotherGamete, NumGenotypes)] += 1.0 / NumGenotypes * 100;
			i++;
		}
		else
		{
			mother.close();
			mother.open("Mother.txt");
			father >> FatherGamete;
		}
	} while (i < NumGenotypes);
	father.close();
	mother.close();
	PrintGenotypes();
	PrintPhenotypes();
}
int main()
{
	unsigned NumFgam = 0, NumMgam = 0;
	std::cout << "Enter number of gametes of father and mother: ";
	std::cin >> NumFgam >> NumMgam;
	MakeCombines(NumFgam * NumMgam);
}