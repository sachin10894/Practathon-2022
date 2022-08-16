#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include<bits/stdc++.h> 
#include<ctime>
#include <chrono>


#define DATA_SIZE 10000000
#define DIM 100
#define NN 10

using namespace std;    

vector<vector <float> > dataset;
vector <float> query(DIM);


// Prototype of a utility function to swap two integers
inline void swapBrute(pair <int,int> *x, pair <int,int> *y);
  
// A class for Max Heap for Brute Force
class MaxHeapforBrute
{
    public:
    pair <int,int> *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of max heap
    int heap_size; // Current number of elements in max heap

    // Constructor
    MaxHeapforBrute(int cap){
        heap_size = 0;
        capacity = cap;
        harr = new pair <int,int>[cap];
    }
  
    // to heapify a subtree with the root at given index
    inline void MaxHeapify(int );
  
    inline int parent(int i) { return (i-1)/2; }
  
    // to get index of left child of node at index i
    inline int left(int i) { return (2*i + 1); }
  
    // to get index of right child of node at index i
    inline int right(int i) { return (2*i + 2); }
  
    // Returns the minimum key (key at root) from max heap
    inline pair <int,int> getMax() { return harr[0]; }
  
    // Inserts a new key 'k'
    inline void insertKey(pair <int,int> k);
};
  
// Constructor: Builds a heap from a given array a[] of given size
  
// Inserts a new key 'k'
inline void MaxHeapforBrute::insertKey(pair <int,int> k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
  
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
  
    // Fix the max heap property if it is violated
    while (i != 0 && harr[parent(i)].second < harr[i].second)
    {
       swapBrute(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
    
// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
inline void MaxHeapforBrute::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && harr[l].second > harr[i].second)
        largest = l;
    if (r < heap_size && harr[r].second > harr[largest].second)
        largest = r;
    if (largest != i)
    {
        swapBrute(&harr[i], &harr[largest]);
        MaxHeapify(largest);
    }
}
  
// A utility function to swap two elements
inline void swapBrute(pair <int,int> *x, pair <int, int> *y)
{
    pair <int,int> temp = *x;
    *x = *y;
    *y = temp;
}


//Initialisation of DATASETMATRIX
inline void initialisationUsingMatrix(){
    
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_real_distribution<> dist {-100.0, 100.0};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };
    
    vector <float> temp;
    for (int i = 0; i< DATA_SIZE;i++){
        temp =  vector <float>(DIM); 
        generate(begin(temp), end(temp), gen);
        dataset.push_back(temp);
    }
    
    //Query Vector
    generate(begin(query), end(query), gen);
}

//BRUTE FORCE Solution
inline void bruteForce_10_nearest(){
    
    float dist;
    int i,j;
    
    MaxHeapforBrute h(NN);

    for( i= 0; i<dataset.size();i++){

        dist = 0;
        for(j = 0;j<query.size();j++){
            dist += abs(dataset[i][j] - query[j]);
        }
        if(i<10)
            h.insertKey(make_pair(i,round(dist)));
        else{
            if(dist<h.getMax().second){
                h.harr[0] = make_pair(i,round(dist));
                h.MaxHeapify(0);
            }

        }
    }

    //cout<<endl<<dataset.size()<<endl;
    for(int x = 0;x<NN;x++){
        cout<<h.harr[x].first<<" "<<h.harr[x].second<<"\t";
    }
    //cout<<endl<<dataset.size()<<endl;
   
}

inline void swap(vector <float> *x, vector <float> *y);
  
// A class for Max Heap for KD TRee
class MaxHeap
{
    public:
    vector <float> *harr; // pointer to array of dataset in heap
    int capacity; // maximum possible size of max heap
    int heap_size; // Current number of elements in max heap

    // Constructor
    MaxHeap(int capacity);
  
    // to heapify a subtree with the root at given index
    inline void MaxHeapify(int );
  
    inline int parent(int i) { return (i-1)/2; }
  
    // to get index of left child of node at index i
    inline int left(int i) { return (2*i + 1); }
  
    // to get index of right child of node at index i
    inline int right(int i) { return (2*i + 2); }
  
    // Returns the minimum key (key at root) from max heap
    inline vector <float> getMax() { return harr[0]; }
  
    // Inserts a new key 'k'
    inline void insertKey(float * arr, int dist);
};
  
// Constructor: Builds a heap from a given array a[] of given size
MaxHeap::MaxHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new vector <float> [cap];
}
  
// Inserts a new key 'k'
inline void MaxHeap::insertKey(float * arr,int dist)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
  
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    vector<float> temp ;
    temp.assign(arr,arr + DIM);
    harr[i] = temp;
    harr[i].push_back(dist);

    // Fix the max heap property if it is violated
    while (i != 0 && harr[parent(i)][DIM] < harr[i][DIM])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
    
// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
inline void MaxHeap::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && harr[l][DIM] > harr[i][DIM])
        largest = l;
    if (r < heap_size && harr[r][DIM] > harr[largest][DIM])
        largest = r;
    if (largest != i)
    {
        swap(&harr[i], &harr[largest]);
        MaxHeapify(largest);
    }
}
  
// A utility function to swap two elements
inline void swap(vector <float> *x, vector <float> *y)
{
    vector <float> temp = *x;
    *x = *y;
    *y = temp;
}

//KD Tree Implementation
// A structure to represent node of kd tree
struct Node
{
    float q[DIM]; // To store k dimensional point
    Node *left, *right;
} * root;
  

// A method to create a node of K D tree
inline struct Node* newNode()
{
    struct Node* temp = new Node;
    // Uniform distribution se fillup the array
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_real_distribution<> dist {-100.0, 100.0};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };
    
    generate(begin(temp->q), end(temp->q), gen);

    temp->left = temp->right = NULL;
    return temp;
}
  
// Inserts a new node and returns root of modified tree, The parameter depth is used to decide axis of comparison
inline Node *insertRec(Node *root, Node * n, unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
       return n;
  
    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % DIM;
  
    // Compare the new point with root on current dimension 'cd and decide the left or right subtree
    if (n->q[cd] < (root->q[cd]))
        root->left  = insertRec(root->left, n, depth + 1);
    else
        root->right = insertRec(root->right, n, depth + 1);
  
    return root;
}
  
// Function to insert a new point with given point in KD Tree and return new root. It mainly uses above recursive function "insertRec()"
inline Node* insert(Node *root, Node * n)
{
    return insertRec(root, n, 0);
}


inline void initialisationUsingKDTree(){
    
    int i;
    root =NULL;
    for(i=0;i<DATA_SIZE;i++){
        root = insert(root, newNode());
    }

    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_real_distribution<> dist {-100.0, 100.0};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };
    
    //Query Vector
    generate(begin(query), end(query), gen);
    
    cout<<"Done initialising Tree and Query"<<endl;
}

void KDTreeApproach(){

    //cout<<"Lets Start"<<endl;
    MaxHeap h(NN);
    Node * temp;
    int dist = 0, i, j=0, k=0;
    int depth = 0;
    temp = root;
    while(temp!=NULL){

        dist = 0;
        for(i= 0;i<query.size();i++){
            dist += abs(temp->q[i] - query[i]);
        }
        //cout<<dist<<" Distance from "<< ++j <<" node"<<endl;
        if (h.heap_size<10){
            //cout<<"Going to insert initial entries"<<endl;
            h.insertKey(temp->q,dist);
            //cout<<"Inserted "<< ++k <<"th node"<<endl;
        }
        else {
            if (dist<h.getMax()[DIM]){
                h.harr[0].assign(temp->q,(temp->q)+DIM);
                h.harr[0].push_back(dist);
                h.MaxHeapify(0);
                //cout<<"Inserted "<< ++k <<"th node"<<endl;
            }
        }
        //cout<<"Heap checked"<<endl;
        //Where to go in KD Tree
        if (query[depth % DIM] < temp->q[depth % DIM]){
            temp = temp->left;
            //cout<<"Moving Left"<<endl;
        }else {
            temp = temp->right;
            //cout<<"Moving Right"<<endl;
        }
        depth++;
    }

    //cout<<"Done with Calculation showing  heap"<<endl; 

    for(int x = 0; x < h.capacity ;x++){
        cout<<h.harr[x][DIM]<<"\t";
    }
}

int coutNodes(Node * root){

    if (root==NULL)
        return 0;

    int ln = coutNodes(root->left);
    int rn = coutNodes(root->right);

    return ln +rn +1;
}

int main(){
    cout<<DATA_SIZE<<" Datasize"<<endl;

    auto timenow =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  
    cout << ctime(&timenow) << endl;
    cout<<"Brute Force Approach"<<endl;
    clock_t time_req;
    time_req = clock();
    initialisationUsingMatrix();  //Initialisation using Matrix Done
    time_req = clock()-time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<< " seconds time taken for initialisation"<<endl;
    
    time_req = clock(); //Processing Start Point
    bruteForce_10_nearest();  //Brute Force Approach Call
    time_req = clock()-time_req; //Processing End point
    cout<<endl<<(float)time_req/CLOCKS_PER_SEC<< " seconds, time taken for calculations\n"<<endl;

    cout<<"KD Tree Approach"<<endl;
    time_req = clock();
    initialisationUsingKDTree();    //initalisationUsingKDTree Done
    time_req = clock()-time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<< " seconds time taken for initialisation"<<endl;
    
    time_req = clock();
    KDTreeApproach();   //KD Tree Approach Call
    //cout<<coutNodes(root)<<" number of Nodes in KD tree"<<endl;
    time_req = clock()-time_req; //Processing End point
    cout<<endl<<(float)time_req/CLOCKS_PER_SEC<< " seconds, time taken for calculations\n"<<endl;

}
