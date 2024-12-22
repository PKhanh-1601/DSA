//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 7
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct EmployeeNode
{
    string name;
    vector<EmployeeNode*> subordinates;

    EmployeeNode(const string& name) : name(name) {}
};

class OrganizationalChart
{
private:
    EmployeeNode* root;
    EmployeeNode* findEmployee(EmployeeNode* node, const string& name)
    {
        if (!node) return NULL;
        if (node->name == name) return node;
        for (EmployeeNode* subordinate : node->subordinates)
        {
            EmployeeNode* found = findEmployee(subordinate, name);
            if (found) return found;
        }
        return NULL;
    }

    void printHierarchy(EmployeeNode* node, int depth)
    {
        if (!node) return;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->name << endl;
        for (EmployeeNode* subordinate : node->subordinates)
        {
            printHierarchy(subordinate, depth + 1);
        }
    }

public:
    OrganizationalChart(const string& ceoName)
    {
        root = new EmployeeNode(ceoName);
    }
    void addEmployee(const string& managerName, const string& employeeName)
    {
        EmployeeNode* manager = findEmployee(root, managerName);
        if (manager)
        {
            manager->subordinates.push_back(new EmployeeNode(employeeName));
        }
        else
        {
            cout << "Manager not found: " << managerName << endl;
        }
    }

    void removeEmployee(const string& employeeName)
    {
        if (root->name == employeeName)
        {
            cout << "Cannot remove the CEO." << endl;
            return;
        }
        removeEmployeeRec(root, employeeName);
    }

    bool removeEmployeeRec(EmployeeNode* node, const string& employeeName)
    {
        if (!node) return false;
        for (auto it = node->subordinates.begin(); it != node->subordinates.end(); ++it)
        {
            if ((*it)->name == employeeName)
            {
                delete *it;
                node->subordinates.erase(it);
                return true;
            }
            if (removeEmployeeRec(*it, employeeName)) return true;
        }
        return false;
    }

    void displayHierarchy()
    {
        printHierarchy(root, 0);
    }
};

int main()
{
    OrganizationalChart orgChart("CEO");

    orgChart.addEmployee("CEO", "VP1");
    orgChart.addEmployee("CEO", "VP2");
    orgChart.addEmployee("VP1", "Manager1");
    orgChart.addEmployee("VP1", "Manager2");
    orgChart.addEmployee("VP2", "Manager3");
    orgChart.addEmployee("Manager1", "Employee1");
    orgChart.addEmployee("Manager1", "Employee2");

    cout << "Organizational Hierarchy:" << endl;
    orgChart.displayHierarchy();

    cout << "\nRemoving Manager1..." << endl;
    orgChart.removeEmployee("Manager1");

    cout << "Organizational Hierarchy after removal:" << endl;
    orgChart.displayHierarchy();

    return 0;
}
