/**
   @author Sho Miyahara 2017
*/

class manip_error{
  friend std::ostream& operator <<(std::ostream& ros, manip_error manip){
    return manip(ros);
  }
private:
  std::string manip_value;
public:
  manip_error(std::string value){
    manip_value = value;
  }
private:
  std::ostream& operator()(std::ostream& ros){
    return ros << "\e[1m\e[31m" << manip_value << "\e[0m";
  }
};
