#include<string>
#include<cmath>
#include<ctime>
#include<fstream>
#include<iostream>
using namespace std;


// ============================================================================

string extension = ".txt";

// ============================================================================




int FT_func(int in, int b)
{
    int s = in + pow(2, b - 1);
    return s;
}



struct c_node;

struct FT_node
{
    int kk;
    c_node* address;
    FT_node* previous, * next;

};

class Finger_Table
{
public:
    FT_node* head, * temp;

    Finger_Table()
    {
        head = NULL;
        temp = nullptr;
    }

    void insert_FT(int k, c_node* c_add)
    {
        if (head == NULL)
        {
            temp = new FT_node;

            temp->kk = k;
            temp->address = c_add;
            temp->next = NULL;
            temp->previous = NULL;
            head = temp;
        }
        else
        {
            FT_node* temp2 = head;
            temp = new FT_node;

            temp->kk = k;
            temp->address = c_add;

            if (temp->kk < temp2->kk)
            {
                temp->next = temp2;
                temp->previous = NULL;
                temp2->previous = temp;
                head = temp2 = temp;
            }
            else
            {
                if (temp2->next != NULL)
                {
                    while (temp->kk >= temp2->next->kk)
                    {
                        temp2 = temp2->next;
                        if (temp2->next == NULL)
                            break;
                    }
                }
                temp->previous = temp2;
                temp->next = temp2->next;
                temp2->next = temp;
            }
        }
    }

    c_node* get_node(int j)
    {
        int k = 0;
        temp = head;
        if (k == j)
            return temp->address;
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
                k++;
                if (k == j)
                    return temp->address;

            }
            return temp->address;
        }
    }

    void display_FT()
    {
        temp = head;

        while (temp != NULL)
        {
            cout << temp->kk << "    ";
            temp = temp->next;
        }
        cout << endl;
    }

    void clear()
    {
        temp = head->next;
        while (temp != NULL)
        {
            delete head;
            head = temp;
            temp = temp->next;
        }
        delete head;
        head = NULL;

    }
};



class Node
{
public:

    int line;
    int key;
    string name;

    Node* left;
    Node* right;

    int height;
};

class AVL
{
public:

    Node* root;
    int het;
    int count;

    int height(Node* N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }


    int max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }


    Node* newNode(int key, string n, int l)
    {
        Node* node = new Node();
        node->key = key;
        node->line = l;
        node->name = n;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;

        return(node);
    }


    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;


        return x;
    }

    void print(int info, string n, int l)
    {
        cout << info << " " << n << " " << l << endl;;
    }


    int get_line(Node* temp, int k)
    {
        if (root == NULL)
        {
            return temp->line;
        }
        if (temp->key == k)
        {
            return temp->line;
        }
        if (temp->left != NULL)
        {
            traverse(temp->left);
        }

        if (temp->right != NULL)
        {
            traverse(temp->right);
        }
    }

    string get_name(Node* temp, int k)
    {
        if (root == NULL)
        {
            return temp->name;
        }
        if (temp->key == k)
        {
            return temp->name;
        }
        if (temp->left != NULL)
        {
            traverse(temp->left);
        }



        if (temp->right != NULL)
        {
            traverse(temp->right);
        }
    }
    void traverse(Node* temp)
    {
        if (root == NULL)
        {
            return;
        }
        if (temp->left != NULL)
        {
            traverse(temp->left);
        }

        print(temp->key, temp->name, temp->line);

        if (temp->right != NULL)
        {
            traverse(temp->right);
        }
        return;
    }
    Node* get_value(Node* root, int key)
    {
        if (root == NULL)
            return root;

        if (root->key == key)
            return root;

        if (root != NULL)
        {
            cout << root->key << " ";
            cout << root->name << " ";
            cout << root->line << " ";
            cout << endl;
            get_value(root->left, key);
            get_value(root->right, key);
        }


    }
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;


        return y;
    }

    int getBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }


    Node* insert(Node* node, int key, string F_name, int l)
    {

        if (node == NULL)
            return(newNode(key, F_name, l));


        if (key < node->key)
            node->left = insert(node->left, key, F_name, l);
        else if (key > node->key)
            node->right = insert(node->right, key, F_name, l);
        else
            return node;


        node->height = 1 + max(height(node->left),
            height(node->right));

        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }


    Node* smallestnode(Node* node)
    {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int key)
    {

        if (root == NULL)
            return root;


        if (key < root->key)
            root->left = deleteNode(root->left, key);

        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node* temp;
                if (root->left)
                {
                    temp = root->left;
                }
                else
                {
                    temp = root->right;
                }
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                Node* temp = smallestnode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }


        if (root == NULL)
            return root;

        root->height = 1 + max(height(root->left),
            height(root->right));

        int balance = getBalance(root);


        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }



    void preOrder(Node* root)
    {
        if (root != NULL)
        {
            cout << root->key << " ";
            cout << root->name << " ";
            cout << root->line << " ";
            cout << endl;
            preOrder(root->left);
            preOrder(root->right);
        }
    }

};




struct c_node
{
    AVL tree;
    int id;
    int index = 0;
    int num_files = 1;
    int line = 0;
    fstream* files = new fstream[num_files];
    Finger_Table ft;
    c_node* first, * next, * previous;

    string name = "file";


};


struct Circular_List
{

    c_node* head, * temp;

    Circular_List()
    {
        head = NULL;
        temp = nullptr;
    }
    void insert(int id1)
    {
        if (head == NULL)
        {

            temp = new c_node;

            string str_id = to_string(id1);
            temp->name += str_id;
            string str_id2 = temp->name;

            str_id2 += to_string(temp->num_files);
            str_id2 += extension;
            temp->files[temp->index].open(str_id2);

            temp->files[temp->index].close();

            temp->id = id1;
            temp->tree.root = NULL;
            temp->next = temp->previous = temp;
            head = temp;
            head->first = head;


        }
        else
        {
            c_node* temp2 = head;
            temp = new c_node;
            temp->id = id1;
            temp->tree.root = NULL;

            string str_id = to_string(id1);
            temp->name += str_id;
            string str_id2 = temp->name;

            str_id2 += to_string(temp->num_files);
            str_id2 += extension;
            temp->files[temp->index].open(str_id2);
            temp->files[temp->index].close();

            if (temp2->next == temp2 && temp2->previous == temp2)
            {
                if (temp->id < temp2->id)
                {
                    temp->next = temp2;
                    temp->previous = temp2->previous;
                    temp2->previous = temp;
                    head = temp2 = temp;
                    head->first = head;
                }
                else if (temp->id > temp2->id)
                {
                    temp->next = temp2->next;
                    temp2->previous = temp;
                    temp->previous = temp2;
                    temp2->next = temp;
                    temp2 = temp;
                }
            }
            else
            {
                if (temp->id < temp2->id)
                {

                    temp->next = temp2;
                    temp->previous = temp2->previous;


                    temp2->previous = temp;
                    temp->previous->next = temp;

                    head = temp2 = temp;
                    head->first = head;

                }
                else if (temp->id > temp2->id)
                {

                    while (temp->id > temp2->next->id)
                    {

                        if (temp2->next == head)
                            break;
                        temp2 = temp2->next;
                    }
                    temp->next = temp2->next;
                    temp2->next->previous = temp;
                    temp->previous = temp2;
                    temp2->next = temp;
                }
            }
        }

    }

    void insert_AVL(int line, string name2, int id1, int key)
    {
        temp = head;
        if (temp->id == id1)
        {
            temp->tree.root = temp->tree.insert(temp->tree.root, key, name2, line);
        }
        else
        {
            temp = temp->next;
            while (temp != head)
            {
                if (temp->id == id1)
                {
                    temp->tree.root = temp->tree.insert(temp->tree.root, key, name2, line);
                    break;
                }
                temp = temp->next;
            }
        }
    }

    void file_handle(string data, c_node* current)
    {
        string name1 = current->name;
        name1 += to_string(current->num_files);
        name1 += extension;


        int c = 0;
        temp = current;

        temp->files[temp->num_files - 1].open(name1, ios::in);
        bool b = temp->files[temp->num_files - 1].is_open();
        cout << b << endl;



        while (temp->files[temp->num_files - 1])
        {
            string ss = "";
            getline(temp->files[temp->num_files - 1], ss);
            cout << ss << endl;
            c++;
        }

        temp->files[temp->num_files - 1].close();


        if (c - 1 >= 5)
        {
            fstream* t_file = new fstream[temp->num_files];
            for (int i = 0; i < temp->num_files; i++)
            {

                string name2 = current->name;
                name2 += to_string(i + 1);
                name2 += extension;


                temp->files[i].open(name2, ios::in);

                t_file[i].open(name2, ios::app);

                while (temp->files[i].eof())
                {
                    string ss = "";
                    getline(temp->files[i], ss);
                    t_file[i] << ss;
                }


                t_file[i].close();
                temp->files[i].close();

                name2 = "";
            }
            temp->num_files++;
            delete[] temp->files;
            temp->files = new fstream[temp->num_files];
            for (int i = 0; i < temp->num_files - 1; i++)
            {
                string name2 = current->name;
                name2 += to_string(i + 1);
                name2 += extension;


                temp->files[i].open(name2, ios::app);
                t_file[i].open(name2, ios::in);
                while (temp->files[i].eof())
                {
                    string ss = "";
                    getline(t_file[i], ss);
                    temp->files[i] << ss;
                }
                temp->files[i].close();

                t_file[i].close();
                name2 = "";
            }

            temp->files[temp->num_files - 1].open(name1, ios::app);
            temp->files[temp->num_files - 1] << data;
            temp->files[temp->index] << "\n";
            temp->files[temp->num_files - 1].close();
            temp->index = temp->num_files - 1;


        }
        else
        {
            temp->files[temp->index].open(name1, ios::app);
            temp->files[temp->index] << data;
            temp->files[temp->index] << "\n";
            temp->files[temp->index].close();


        }


        cout << endl << endl << endl << endl;
    }

    string get_filename(c_node* temp2)
    {
        string n1 = "file";

        n1 += to_string(temp2->id);
        n1 += to_string(temp2->num_files);
        n1 += extension;

        return n1;
    }

    int get_fileline(c_node* temp2)
    {
        string n1 = "file";
        n1 += to_string(temp2->id);
        n1 += to_string(temp2->num_files);
        n1 += extension;

        int line = 0;

        temp2->files[temp2->num_files - 1].open(n1, ios::in);
        while (temp2->files[temp2->num_files - 1])
        {
            string ss = "";
            getline(temp2->files[temp2->num_files - 1], ss);
            line++;
        }
        temp2->files[temp2->num_files - 1].close();
        return line - 1;
    }





    void file_check_id(int id1, string data)
    {
        temp = head;
        if (temp->id == id1)
        {
            file_handle(data, temp);
        }
        else
        {
            temp = temp->next;
            while (temp->next != head)
            {
                if (temp->id == id1)
                {
                    file_handle(data, temp);
                    break;
                }
                temp = temp->next;
            }
        }
    }
    bool check_id(long long ID)
    {

        temp = head;
        if (temp != NULL)
        {
            if (temp->id == ID)
            {

                return true;
            }
            temp = temp->next;
        }
        while (temp != head)
        {
            if (temp->id == ID)
            {

                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    void update_machine(int key, int bit)
    {


        insert(key);
        set_ftable(bit);
        temp = head;
        c_node* temp2 = head;
        c_node* temp3 = head;

        while (temp->next != head)
        {
            if (temp->id == key)
            {
                temp2 = temp->next;
                break;
            }
            temp = temp->next;
        }

        temp->tree.root = NULL;


        string value = "";
        if (temp2->tree.root != NULL)
        {
            for (int i = temp->previous->id + 1; i <= key; i++)
            {

                temp3->tree.root = temp2->tree.get_value(temp2->tree.root, i);


                value = get_data(temp2, temp2->tree.root->name, temp2->tree.root->line);


                file_handle(value, temp);

                temp->tree.root = temp->tree.insert(temp->tree.root, i, get_filename(temp), get_fileline(temp));

                temp2->tree.deleteNode(temp2->tree.root, i);
            }
            temp->tree.preOrder(temp->tree.root);
        }

    }

    void Remove_machine(int key)
    {


        int n = 1;
        temp = head;
        temp->ft.temp = temp->ft.head;

        if (key <= temp->ft.temp->kk)
        {
            temp = temp->ft.temp->address;
            cout << " jumping into machine :- " << temp->id << endl;
        }
        else
        {

            while (temp->ft.temp->next != NULL)
            {
                cout << "shoiwng the temp next kk value " << temp->ft.temp->next->kk << endl;

                if (key == temp->ft.temp->kk)
                {
                    temp = temp->ft.temp->address;
                    temp->ft.temp = temp->ft.head;
                    cout << "1:  jumping into machine :- " << temp->id << endl;
                    n++;
                    break;
                }
                if (key < temp->ft.temp->next->kk)
                {
                    temp = temp->ft.temp->address;
                    temp->ft.temp = temp->ft.head;
                    cout << "2: jumping into machine :- " << temp->id << endl;
                    n++;
                }
                else
                {
                    temp->ft.temp = temp->ft.temp->next;
                }
                cout << "into machine " << temp->id << endl;
            }
        }
        if (n == 1)
            temp = temp->ft.temp->address;
        cout << "1 : showing deleting node id " << temp->id << endl;

        c_node* temp3 = temp;
        c_node* temp2 = temp->next;

        temp3->tree.root = NULL;


        string value = "";
        if (temp->tree.root != NULL)
        {

            for (int i = ((temp->previous->id) + 1); i <= key; i++)
            {

                temp3->tree.root = temp->tree.get_value(temp->tree.root, i);

                value = get_data(temp, temp3->tree.root->name, temp3->tree.root->line);
                file_handle(value, temp2);
                temp2->tree.root = temp2->tree.insert(temp2->tree.root, i, get_filename(temp2), get_fileline(temp2));
                temp->tree.deleteNode(temp->tree.root, i);
            }
            temp2->tree.preOrder(temp2->tree.root);
        }
        // c_node* temp2 = temp->next;

        if (temp == head)
        {
            temp2->previous = temp->previous;
            temp->previous->next = temp2;
            head = temp->previous;
            delete temp;
        }
        else {
            temp2->previous = temp->previous;
            temp->previous->next = temp2;
            delete temp;
        }
        /*temp->previous->next = temp2;
        temp2->previous = temp->previous;
        cout << "2 : showing deleting node id " << temp->id << endl;
        cout << "3 : showing deleting node id " << temp2->id << endl;
        delete temp;*/




    }



    void Remove_data(int k)
    {
        int n = 1;
        temp = head;
        temp->ft.temp = temp->ft.head;
        while (k > temp->ft.temp->kk || temp == head->previous)
        {
            if (k > temp->ft.temp->kk)
            {
                temp = temp->ft.temp->address;
                n++;
            }
        }
        int l;
        string na;
        l = temp->tree.get_line(temp->tree.root, k);
        na = temp->tree.get_name(temp->tree.root, k);
        string blank = " ";
        temp->files[na[5]].open(na);
        int l1 = 0;
        while (temp->files[na[5]].eof())
        {
            l1++;
            if (l1 == l)
            {
                temp->files[na[5]] << blank;
                break;
            }
        }
        temp->files[na[5]].close();
        temp->tree.root = temp->tree.deleteNode(temp->tree.root, k);
    }

    void set_ftable(int bit)
    {
        temp = head;
        int value = 0;
        c_node* temp2 = head;
        c_node* temp3 = NULL;
        temp2 = head;
        int i = 0;


        while (temp2->next != head)
        {
            Finger_Table f;

            cout << temp2->id << " showing id" << endl;

            for (int j = 1; j <= bit; j++)
            {
                value = set_value(FT_func(temp2->id, j));
                temp3 = get_adress(value);
                f.insert_FT(value, temp3);
            }
            temp2->ft = f;
            temp2->ft.display_FT();

            for (int i = 0; i < bit; i++)
            {
                temp3 = temp2->ft.get_node(i);
            }
            cout << endl << endl << endl;

            f.head = NULL;
            temp2 = temp2->next;
        }

        Finger_Table f;

        cout << temp2->id << " shoing id" << endl;
        for (int j = 1; j <= bit; j++)
        {
            value = set_value(FT_func(temp2->id, j));
            temp3 = get_adress(value);
            f.insert_FT(value, temp3);
        }
        temp2->ft = f;
        temp2->ft.display_FT();

        for (int i = 0; i < bit; i++)
        {
            temp3 = temp2->ft.get_node(i);
        }
        cout << endl;
    }



    int set_value(int v)
    {
        temp = head;
        while (v > temp->id)
        {
            if (temp->next == head)
            {
                temp = head;
                break;
            }
            temp = temp->next;
        }
        return temp->id;
    }

    c_node* get_adress(int val)
    {
        temp = head;
        while (temp->next != head)
        {
            if (temp->id == val)
                break;
            else
                temp = temp->next;
        }
        return temp;
    }

    string get_data(c_node* temp2, string file, int line)
    {
        string name = "file";
        name += to_string(temp2->id);
        string name1 = name;
        int line2 = 1;
        string answer = "";
        for (int i = 0; i < temp2->num_files; i++)
        {

            name1 += to_string(i + 1);
            name1 += extension;
            if (file == name1)
            {
                cout << name1 << endl;
                temp2->files[i].open(name1, ios::in);


                while (temp2->files[i].eof())
                {

                    getline(temp2->files[i], answer);


                    if (line == line2)
                    {
                        //getline(temp2->files[i], answer);
                        return answer;
                    }
                    line2++;
                }
                temp2->files[i].close();
            }
        }
    }


    int get_ID(int i)
    {
        temp = head;
        for (int k = 1; k < i; k++)
        {
            temp = temp->next;
        }
        return temp->id;
    }


    void show_id()
    {

        temp = head;
        cout << temp->id << "   ";
        temp = temp->next;

        while (temp != head)
        {
            cout << temp->id << "   ";
            temp = temp->next;
        }
        cout << endl;
    }

    void display()
    {
        temp = head;
        cout << "id= " << temp->id << endl;
        //temp->tree.preOrder(temp->tree.root);
        temp->tree.traverse(temp->tree.root);
        cout << endl;
        temp = temp->next;
        while (temp != head)
        {
            cout << "id= " << temp->id << endl;
            temp->tree.preOrder(temp->tree.root);
            cout << endl;
            temp = temp->next;
        }
    }

};

long long polynomialRollingHash(string const& str)
{
    int p = 31;
    int m = 1e9 + 9;
    long long power_of_p = 1;
    long long hash_val = 0;

    // Loop to calculate the hash value
    // by iterating over the elements of string
    for (int i = 0; i < str.length(); i++) {
        hash_val = (hash_val + (str[i] - 'a' + 1) * power_of_p) % m;

        power_of_p = (power_of_p * p) % m;
    }
    return hash_val;
}







int main()
{


    cout << "showing---------------------" << endl;
    string prompt = "";

    int input = -1;
    int bits = 0;
    long long range = 0;
    int machines = 0;
    string str;
    long long id = 0;
    bool b = true;


    do
    {
        cout << "your input should not exceed 64  " << endl;
        cout << "enter the number of bits you want to work on " << endl;
        cin >> bits;
    } while (bits > 64);
    cout << endl << endl;

    cout << "ENTER THE NUMBER OF MACHINES/NODES YOU WANT " << endl;
    cin >> machines;

    range = pow(2, bits);

    cout << "if you want to assign ids manually then press 0, if you want to assign ids automatically then press 1. " << endl;
    cin >> input;


    Circular_List* obj1 = new Circular_List;
    int line = 1;

    int key = 3;
    if (input == 0)
    {
        for (int i = 0; i < machines; i++)
        {

            cout << "enter machine : " << i + 1 << " ID " << endl;
            cin >> input;
            input = input % range;

            obj1->insert(input);
        }
    }
    else if (input == 1)
    {
        cin.ignore();
        for (int i = 0; i < machines; i++)
        {
            Finger_Table ft;

            cout << "enter the IP address of machine: " << i + 1 << endl;
            getline(cin, str);
            cout << str << endl;
            id = polynomialRollingHash(str);
            //cout << id << " showing id in auto assign " << endl;
            id = id % range;
            if (id < 0)
                id *= -1;
            cout << id << " showing id in auto assign " << endl;
            if (i >= 0)
            {
                while (b != false)
                {

                    b = obj1->check_id(id);
                    cout << b << " into the while in auto assign " << endl;
                    if (b == true)
                        id += 2;
                }
                cout << "revised id " << id << endl;
                obj1->insert(id);
            }
            b = true;
        }

    }
    obj1->show_id();

    obj1->set_ftable(bits);

    obj1->show_id();
    int id1 = 0;
    do {
        int aa = 0;
        int j = 0;
        //cin.ignore();
        if (prompt == "again" || prompt == "AGAIN")
        {
            prompt = "enter";
        }
        else
        {
            cout << "if you want to enter data write ENTER " << endl;
            getline(cin, prompt);
        }
        if (prompt == "ENTER" || prompt == "enter")
        {
            obj1->show_id();
            cout << "enter id of the machine in which you want to insert data " << endl;
            cin >> id;

            do {

                cin.ignore();

                input = 0;
                cout << "enter DATA " << endl;
                getline(cin, str);


                id1 = polynomialRollingHash(str);
                id1 = id1 % range;



                /*  if (id < id1)
                  {
                      cout << "you cannt insert in this machine, but you can insert in " << obj1->set_value(id1) << " : machine, input 0 to enter in the given machine " << endl;
                      cin >> input;
                      if (input == 0)
                      {
                          id = obj1->set_value(id1);
                      }
                  }*/
                obj1->file_handle(str, obj1->get_adress(id));

                obj1->get_filename(obj1->get_adress(id));

                obj1->get_fileline(obj1->get_adress(id));
                cout << "done with file handling " << endl;

                obj1->temp = obj1->get_adress(id);

                int a = obj1->get_fileline(obj1->get_adress(id));

                cout << "showing a " << a << endl;
                obj1->insert_AVL(obj1->get_fileline(obj1->get_adress(id)), obj1->get_filename(obj1->get_adress(id)), obj1->set_value(id), FT_func(id, j));
                j++;
                cout << "done with insertion " << endl;

                cout << "enter 4 to stop entering data" << endl; cin >> aa;
                input = 1;
            } while (aa != 4);
        }

        cin.ignore();
        cout << "if you want to enter more data write AGAIN, if not enter END" << endl;
        getline(cin, prompt);
        if (prompt == "end" || prompt == "END")
        {
            break;
        }

    } while (prompt != "end" || prompt != "END");

    /*  obj1->temp = obj1->get_adress(id);
      obj1->temp->tree.preOrder(obj1->temp->tree.root);
      cout << "done with PREORDER " << endl;
      obj1->temp->tree.traverse(obj1->temp->tree.root);

      obj1->temp->tree.deleteNode(obj1->temp->tree.root, 2);

      obj1->temp->tree.preOrder(obj1->temp->tree.root);
      cout << "done with PREORDER " << endl;
      obj1->temp->tree.traverse(obj1->temp->tree.root);*/
      /* obj1->temp->next->tree.preOrder(obj1->temp->next->tree.root);
       obj1->temp->next->tree.traverse(obj1->temp->next->tree.root);
      */ string prompt1 = "";
      obj1->display();
      cin.ignore();
      bool final = true;
      while (final)
      {
          cout << "write MACHINE to enter a new machine, if you want to remove a machine write REMOVE " << endl;
          getline(cin, prompt1);
          if (prompt1 == "MACHINE" || prompt1 == "machine")
          {
              obj1->show_id();

              cout << "enter the id of new machine " << endl;
              cin >> id;
              obj1->update_machine(id, bits);
          }
          else if (prompt1 == "remove" || prompt1 == "REMOVE")
          {
              obj1->show_id();

              cout << "enter the id of machine you want to remove " << endl;
              cin >> id;
              obj1->Remove_machine(id);
              cout << "showing nodes after removal " << endl;
              obj1->show_id();
          }
          obj1->display();
          cin.ignore();
          cout << "write data to remove particular data from a machine " << endl;
          getline(cin, prompt1);
          if (prompt1 == "data" || prompt1 == "DATA")
          {
              cout << "enter the id of machine whose data you want to remove" << endl;
              cin >> id;
              obj1->Remove_data(id);
          }
          int ex;
          cout << "Write 4 to exit ";
          cin >> ex;
          if (ex == 4)
          {
              final = false;
          }
      }
      return 0;
}