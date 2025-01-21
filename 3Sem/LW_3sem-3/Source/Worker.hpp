#pragma once

#include <string>
#include <cstdlib> // Для std::rand и std::srand
#include <ctime>   // Для std::time
#include <fstream>
#include <stdexcept>

#include "../../LW_3sem-1/Source/DynamicArray.hpp"


class Worker {
public:
  unsigned int age;              
  char gender;                    
  std::string education;                
  std::string job;                  
  unsigned int experience;              
  unsigned int salary;          

  Worker();

  Worker(Worker const &);

  Worker(Worker &&);

  Worker(unsigned int const &, 
         char const &, 
         std::string const &, 
         std::string const &, 
         unsigned int const &, 
         unsigned int const &);
  
  Worker & operator=(Worker const &);

  bool operator==(Worker const &) const;
  bool operator!=(Worker const &) const;
  bool operator>(Worker const &) const;
  bool operator>=(Worker const &) const;
  bool operator<=(Worker const &) const;
  bool operator<(Worker const &) const;
};

Worker::Worker():
  age(30),
  gender('m'),
  education("Bachelor's"),
  job("Software Engineer"),
  experience(3),
  salary(45000)
{ }

Worker::Worker(
  unsigned int const & age, 
  char const & gender, 
  std::string const & education, 
  std::string const & job, 
  unsigned int const & experience, 
  unsigned int const & salary):
  age(age), 
  gender(gender),
  education(education), 
  job(job),
  experience(experience),
  salary(salary)
{ }

Worker::Worker(Worker const & other):
  age(other.age), 
  gender(other.gender),
  education(other.education), 
  job(other.job),
  experience(other.experience),
  salary(other.salary)
{ }

Worker::Worker(Worker && other):
  age(std::move(other.age)), 
  gender(std::move(other.gender)),
  education(std::move(other.education)), 
  job(std::move(other.job)),
  experience(std::move(other.experience)),
  salary(std::move(other.salary))
{ }

Worker & Worker::operator=(Worker const & other)
{
  if (this != &other)
  {
    age = other.age;
    gender = other.gender;
    education = other.education;
    job = other.job;
    experience = other.experience;
    salary = other.salary;
  }
  return *this;
}

bool Worker::operator==(Worker const & other) const
{
  if((age == other.age) &&
     (gender == other.gender) &&
     (education == other.education) &&
     (job == other.job) &&
     (experience == other.experience) &&
     (salary == other.salary))
    return true;
  return false;
}

bool Worker::operator!=(Worker const & other) const
{
  return !operator==(other);
}

bool Worker::operator>(Worker const & other) const
{
  if (age > other.age)
    return true;
  else if (age == other.age)
  {
    if (gender > other.gender)
      return true;
    else if (gender == other.gender)
    {
      if (education > other.education)
        return true;
      else if (education == other.education)
      {
        if (job > other.job)
          return true;
        else if (job == other.job)
        {
          if (experience > other.experience)
            return true;
          else if (experience == other.experience)
          {
            if (salary > other.salary)
              return true;
            else if (salary == other.salary)
            {
              return false;
            }
            else 
              return false; 
          }
          else 
            return false;              
        }
        else 
          return false;        
      }
      else 
        return false;    
    }
    else 
      return false;
  }
  else 
    return false;
}

bool Worker::operator>=(Worker const & other) const
{
  if (age > other.age)
    return true;
  else if (age == other.age)
  {
    if (gender > other.gender)
      return true;
    else if (gender == other.gender)
    {
      if (education > other.education)
        return true;
      else if (education == other.education)
      {
        if (job > other.job)
          return true;
        else if (job == other.job)
        {
          if (experience > other.experience)
            return true;
          else if (experience == other.experience)
          {
            if (salary > other.salary)
              return true;
            else if (salary == other.salary)
            {
              return true;
            }
            else 
              return false; 
          }
          else 
            return false;              
        }
        else 
          return false;        
      }
      else 
        return false;    
    }
    else 
      return false;
  }
  else 
    return false;
}

bool Worker::operator<=(Worker const & other) const
{
  return !operator>(other);
}

bool Worker::operator<(Worker const & other) const
{
  return !operator>=(other);
}


void readWorkersFromFile(DynamicArray<Worker> & workers, std::string const & filename)
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error with opening file: " << filename << std::endl;
    return;
  }
  std::string line;

  while (std::getline(file, line)) {
    Worker worker;
    try
    {    
      size_t pos = 0;

      pos = line.find(',');
      worker.age = std::stoi(line.substr(0, pos));
      line.erase(0, pos + 1);

      worker.gender = line[0];
      line.erase(0, line.find(',') + 1);

      pos = line.find(',');
      worker.education = line.substr(0, pos);
      line.erase(0, pos + 1);

      pos = line.find(',');
      worker.job = line.substr(0, pos);
      line.erase(0, pos + 1);

      pos = line.find(',');
      worker.experience = std::stoi(line.substr(0, pos));
      line.erase(0, pos + 1);

      worker.salary = std::stoi(line); // Последнее значение в строке

      workers.append(worker);
    }
    catch(...)
    {
      continue;
    }
  }
  file.close();
}


/*

void fillArrayRandomly(DynamicArray<Person> & array)
{
  const std::string maleNames[] = {
      "Bob", "Charlie", "Frank", "Isaac", "Jack",
      "Liam", "Noah", "Paul", "Samuel", "Victor",
      "Zach", "Benjamin", "Daniel", "George", "Ian",
      "Kevin", "Michael", "Oscar", "Steve", "Walter",
      "Aiden", "Carter", "Ethan", "Gavin", "Jasper",
      "Leo", "Nathan", "Parker", "Tyler", "Wyatt",
      "Adrian", "Caleb", "Derek", "Finn", "Henry",
      "Jordan", "Kendall", "Miles", "Oliver", "Ryder",
      "Tristan", "Aaron", "Dante", "Freddie", "Hector",
      "Leonard", "Nicolas", "Preston", "Silas", "Tobias",
      "Ulysses", "Winston", "Zane", "Brandon", "Dylan",
      "Elijah", "Graham", "Isaiah", "Kendrick", "Mason",
      "Owen", "Paxton", "Soren", "Uriah", "Wesley"
  };
  const size_t maleNames_size = sizeof(maleNames)/sizeof(maleNames[0]);

  const std::string femaleNames[] = {
      "Alice", "Diana", "Eve", "Grace", "Hannah",
      "Katherine", "Mia", "Olivia", "Quinn", "Rachel",
      "Tina", "Ursula", "Wendy", "Yara", "Amelia",
      "Chloe", "Ella", "Fiona", "Holly", "Julia",
      "Laura", "Nina", "Penny", "Rita", "Tara",
      "Uma", "Vera", "Xena", "Brianna", "Delilah",
      "Faith", "Hazel", "Ivy", "Kylie", "Maya",
      "Ophelia", "Riley", "Sophie", "Violet", "Zoe",
      "Bella", "Elena", "Giselle", "Isabella", "Luna",
      "Nora", "Paige", "Samantha", "Vanessa", "Yasmine",
      "Bianca", "Cynthia", "Evelyn", "Gina", "Irene",
      "Kara", "Maddie", "Opal", "Rosie", "Vera",
      "Alyssa", "Carmen", "Felicity", "Holly", "Jade",
      "Lila", "Nadia", "Quinlan", "Rhea", "Talia",
      "Violet", "Xena"
  };
  const size_t femaleNames_size = sizeof(femaleNames)/sizeof(femaleNames[0]);

  const std::string surnames[] = {
    "Smith", "Johnson", "Williams", "Jones", "Brown",
    "Davis", "Miller", "Wilson", "Moore", "Taylor",
    "Anderson", "Thomas", "Jackson", "White", "Harris",
    "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
    "Clark", "Rodriguez", "Lewis", "Lee", "Walker",
    "Hall", "Allen", "Young", "Hernandez", "King",
    "Wright", "Lopez", "Hill", "Scott", "Green",
    "Adams", "Baker", "Gonzalez", "Nelson", "Carter",
    "Mitchell", "Perez", "Roberts", "Turner", "Phillips",
    "Campbell", "Parker", "Evans", "Edwards", "Collins",
    "Stewart", "Sanchez", "Morris", "Rogers", "Reed",
    "Cook", "Morgan", "Bell", "Murphy", "Bailey",
    "Rivera", "Cooper", "Richardson", "Cox", "Howard",
    "Ward", "Torres", "Peterson", "Gray", "Ramirez",
    "James", "Watson", "Brooks", "Kelly", "Sanders",
    "Price", "Bennett", "Wood", "Barnes", "Ross",
    "Henderson", "Coleman", "Jenkins", "Perry", "Powell",
    "Long", "Patterson", "Hughes", "Flores", "Washington",
    "Butler", "Simmons", "Foster", "Gonzales", "Bryant",
    "Alexander", "Russell", "Griffin", "Diaz", "Hayes"
};
  const size_t surnames_size = sizeof(surnames)/sizeof(surnames[0]);

  std::srand(static_cast<unsigned int>(std::time(0)));

  const size_t size = array.getSize();

  for (size_t index = 0; index < size; index++)
  {
    Person buffer;
    buffer.gender = (std::rand() % 2 == 0) ? 'm' : 'f';
    buffer.age = 18 + std::rand() % (100 - 18);
    buffer.name = (buffer.gender == 'm') ? maleNames[std::rand() % maleNames_size] : femaleNames[std::rand() % femaleNames_size]; 
    buffer.surname = surnames[std::rand() % surnames_size]; 
    buffer.height = 1.5 + (static_cast<double>(std::rand()) / RAND_MAX) * (2.1 - 1.5);
    buffer.isEmployed = (std::rand() % 5 == 4) ? false : true;
    buffer.salary = (buffer.isEmployed) ? ((static_cast<float>(std::rand()) / RAND_MAX) * (15000)) : 0;
    array[index] = Person(std::move(buffer)); 
  }
}
*/