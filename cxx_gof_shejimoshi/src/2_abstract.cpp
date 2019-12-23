#include <iostream>
#include <vector>
using namespace std;

//数据库访问有关的基类
class IDBConnection{
    
};

class IDBCommand{
    
};

class IDataReader{
public:
    virtual void read() { cout << "IDataReader" << endl; } 
};


class IDBFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
    virtual IDBCommand* CreateDBCommand()=0;
    virtual IDataReader* CreateDataReader()=0;
   
   IDBFactory() {}
    virtual ~IDBFactory() {}
};


//支持SQL Server
class SqlConnection: public IDBConnection{
    
};
class SqlCommand: public IDBCommand{
    
};
class SqlDataReader: public IDataReader{
    void read() { cout << "SqlDataReader" << endl; } 
};


class SqlDBFactory:public IDBFactory{
public:
    IDBConnection* CreateDBConnection() {
        return new SqlConnection();
    }
    IDBCommand* CreateDBCommand() {
        return new SqlCommand();
    }
    IDataReader* CreateDataReader() {
        return new SqlDataReader();
    }

    SqlDBFactory() {}
    ~SqlDBFactory() {}
 
};

//支持Oracle
class OracleConnection: public IDBConnection{
    
};

class OracleCommand: public IDBCommand{
    
};

class OracleDataReader: public IDataReader{
    void read() { cout << "OracleDataReader" << endl; } 
};

class OracleDBFactory:public IDBFactory{
public:
    IDBConnection* CreateDBConnection() {
        return new OracleConnection();
    }
    IDBCommand* CreateDBCommand() {
        return new OracleCommand();
    }
    IDataReader* CreateDataReader() {
        return new OracleDataReader();
    }
 
    OracleDBFactory() {}
    ~OracleDBFactory() {}
};



class EmployeeDAO {
    IDBFactory* m_dbFactory;
    
public:

    EmployeeDAO(IDBFactory* dbFactory) {
        this->m_dbFactory=dbFactory;
    }
    vector<int> GetEmployees(){
        IDBConnection* connection =
            m_dbFactory->CreateDBConnection();
        // connection->ConnectionString("...");

        IDBCommand* command =
            m_dbFactory->CreateDBCommand();
        // command->CommandText("...");
        // command->SetConnection(connection); //关联性

        IDataReader* reader = 
            m_dbFactory->CreateDataReader(); //关联性
        // read ...
    }
};

int main() 
{
    IDBFactory *idf = new OracleDBFactory();
    IDataReader* ir = idf->CreateDataReader();
    ir->read();
    // EmployeeDAO dao(idf);
    // dao.GetEmployees();

    if(idf) {
        delete idf;
    }

    return 0;
}
