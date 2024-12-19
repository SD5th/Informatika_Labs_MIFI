#pragma once

#include <string>
#include <cstdlib> // Для std::rand и std::srand
#include <ctime>   // Для std::time

#include "../../LW_3sem-1/Source/DynamicArray.hpp"


class Person {
public:
  char gender;
  unsigned int age;              
  std::string name; 
  std::string surname;  
  double height;     
  bool isEmployed;             
  float salary;          

  Person();

  Person(Person const &);

  Person(Person &&);

  Person(char const &, 
         unsigned int const &, 
         std::string const &, 
         std::string const &, 
         double const &, 
         bool const &, 
         float const &);
  
  Person & operator=(Person const &);

  bool operator==(Person const &) const;
  bool operator!=(Person const &) const;
  bool operator>(Person const &) const;
  bool operator>=(Person const &) const;
  bool operator<=(Person const &) const;
  bool operator<(Person const &) const;
};

Person::Person():
  gender('m'),
  age(30),
  name("John"),
  surname("Smith"),
  height(1.75),
  isEmployed(false),
  salary(0.0)
{ }

Person::Person(
  char const & gender, 
  unsigned int const & age, 
  std::string const & name, 
  std::string const & surname, 
  double const & height, 
  bool const & isEmployed, 
  float const & salary):
  gender(gender),
  age(age), 
  name(name), 
  surname(surname),
  height(height),
  isEmployed(isEmployed), 
  salary(salary)
{ }

Person::Person(Person const & other):
  gender(other.gender),
  age(other.age), 
  name(other.name), 
  surname(other.surname),
  height(other.height),
  isEmployed(other.isEmployed), 
  salary(other.salary)
{ }

Person::Person(Person && other):
  gender(std::move(other.gender)),
  age(std::move(other.age)), 
  name(std::move(other.name)), 
  surname(std::move(other.surname)),
  height(std::move(other.height)),
  isEmployed(std::move(other.isEmployed)), 
  salary(std::move(other.salary))
{ }

Person & Person::operator=(Person const & other)
{
  if (this != &other)
  {
    gender = other.gender;
    age = other.age;
    name = other.name;
    surname = other.surname;
    height = other.height;
    isEmployed = other.isEmployed;
    salary = other.salary;
  }
  return *this;
}

bool Person::operator==(Person const & other) const
{
  if((gender == other.gender) &&
     (age == other.age) &&
     (name == other.name) &&
     (surname == other.surname) &&
     (height == other.height) &&
     (isEmployed == other.isEmployed) &&
     (salary == other.salary))
    return true;
  return false;
}

bool Person::operator!=(Person const & other) const
{
  return !operator==(other);
}

bool Person::operator>(Person const & other) const
{
  if (gender > other.gender)
    return true;
  else if (gender == other.gender)
  {
    if (age > other.age)
      return true;
    else if (age == other.age)
    {
      if (name > other.name)
        return true;
      else if (name == other.name)
      {
        if (surname > other.surname)
          return true;
        else if (surname == other.surname)
        {
          if (height > other.height)
            return true;
          else if (height == other.height)
          {
            if (isEmployed > other.isEmployed)
              return true;
            else if (isEmployed == other.isEmployed)
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
  else 
    return false;
}

bool Person::operator>=(Person const & other) const
{
  if (gender > other.gender)
    return true;
  else if (gender == other.gender)
  {
    if (age > other.age)
      return true;
    else if (age == other.age)
    {
      if (name > other.name)
        return true;
      else if (name == other.name)
      {
        if (surname > other.surname)
          return true;
        else if (surname == other.surname)
        {
          if (height > other.height)
            return true;
          else if (height == other.height)
          {
            if (isEmployed > other.isEmployed)
              return true;
            else if (isEmployed == other.isEmployed)
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
  return false;
}

bool Person::operator<=(Person const & other) const
{
  return !operator>(other);
}

bool Person::operator<(Person const & other) const
{
  return !operator>=(other);
}




bool compareAge(Person const & p1, Person const & p2)
{
  if (p1.age > p2.age)
    return true;
  else if (p1.age < p2.age)
    return false;
  else
    return p1 > p2;
}

bool compareSalary(Person const & p1, Person const & p2)
{
  if (p1.salary > p2.salary)
    return true;
  else if (p1.salary < p2.salary)
    return false;
  else
    return p1 > p2;
}

bool compareHeight(Person const & p1, Person const & p2)
{
  if (p1.height > p2.height)
    return true;
  else if (p1.height < p2.height)
    return false;
  else
    return p1 > p2;
}


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