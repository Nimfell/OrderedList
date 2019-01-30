//---------------------------------------------------------------------------
#ifndef OrderedListH
#define OrderedListH
//---------------------------------------------------------------------------

#include <typeinfo.h>  // for 'typeid' to work

template <class T>
     class Node
     {
        public:
          T value;
          Node* next;
          Node* prev;

          Node(T valueNode)
          {
               value = valueNode;
               next = NULL;
               prev = NULL;
          }
     };

template <class T>
  class OrderedList
  {

     private:
          bool _ascending;

     public:
          Node<T>* head;
          Node<T>* tail;

     OrderedList(bool asc)
     {
          head = NULL;
          tail = NULL;
          _ascending = asc;
     }

    int Compare(T v1, T v2)
    {
      if ( typeid(T) == typeid(String))
      {
          AnsiString str_1 = DeleteSpaces(v1);
          AnsiString str_2 = DeleteSpaces(v2);
          int L1 = str_1.Length();
          int L2 = str_2.Length();

          int min_length;                        // get min length for comparison
          if (L1 > L2) min_length = L2;
          else         min_length = L1;

          for (int i = 1; i < min_length; ++i)   // compare the symbols
          {
               if (str_1[i] < str_2[i])      return -1;
               else if (str_1[i] > str_2[i]) return 1;
          }
          
          if (L1 < L2)  return -1;               // compare the length
          if (L1 > L2)  return  1;
          if (L1 == L2) return  0;
      }
      else
      {
        if (v1 < v2)  return -1;                 // universal comparison
        if (v1 == v2) return  0;
        if (v1 > v2)  return  1;
      }
    }


    void Add(T value)
    {
       Node<T>* node = head;
       Node<T>* new_node = new Node<T>(value);

       if (!_ascending)
       {
          while (node != NULL)
          {
               int i = Compare(node->value, new_node->value);

               if ( i == 0 || i == -1)
               {    insert_after(node->prev, new_node);
                    return;  // exit
               }
               node = node->next;
          }
          add_in_tail(new_node);
       }

       else if (_ascending)  
       {
          while (node != NULL)
          {
               int i = Compare(node->value, new_node->value);
               if ( i == 0 || i == 1)
               {    insert_after(node->prev, new_node);
                    return;  // exit
               }
               node = node->next;
          }
          add_in_tail(new_node);
       }
    }

    Node<T>* Find(T val)
    {
        Node<T>* node = head;

        while (node != NULL)
        {

            if (node->value == val)
                return node;
            if (_ascending && node->value > val) return NULL;
            if (!_ascending && node->value < val) return NULL;
            node = node->next;
        }
        return NULL;
    }

    void Delete(T val)
    {
         Node<T>* node = head ;
         while (node != NULL)
         {   if (node->value == val)
             {
                if (node == head && node == tail)
                {   head = NULL;
                    tail = NULL;
                    return;
                }
                if (node == head)
                {   head = node->next ;
                    head->prev = node->prev ;
                    return;
                }
                if (node == tail)
                {   tail = tail->prev;
                    tail -> next = NULL;
                    return;
                }
                else
                {   node->prev->next = node->next;
                    node->next->prev = node->prev;
                    return ;
                }
             }
             node = node->next ;
         }
    }

    void Clear(bool asc)
    {
        _ascending = asc;
        Node<T>* node = head;
        while(node != NULL)
        {
            Node<T>* node_del = node;
            node = node->next;
            delete node_del;
        }
        head = NULL;
        tail = NULL;  
    }

    int Count()
    {
        int count = 0;
        Node<T>* node = head;
        while(node != NULL)
        {
            count++;
            node = node->next;
        }
       return count;
    }

    T* GetAll()     // give the filing of ordered list as array 
    {
        int count = Count();
        Node<T>* node = head;
        T* list = new T[count];

        for(int i = 0; node != NULL; i++)
        {
            list[i] = node->value;
            node = node->next;
        }
        return list;
    }

    protected:  //----------------------------------------------
    void insert_after(Node<T>* nodeAfter, Node<T>* nodeToInsert)
    {
          if (nodeAfter == NULL)
          {
               if (head == NULL)
               {
                    add_in_tail(nodeToInsert);
                    return;
               }
               else
               {
                    head->prev = nodeToInsert;
                    nodeToInsert->next = head;
                    head = nodeToInsert;
                    return;
               }
          }
          nodeToInsert->next = nodeAfter->next ;
          nodeToInsert->prev = nodeAfter ;
          nodeAfter->next = nodeToInsert ;

          if (nodeAfter == tail)
          {   tail = nodeToInsert ;
          }
          else nodeToInsert->next->prev = nodeToInsert ;
    }

    void add_in_tail(Node<T>* item)
    {
       if (head == NULL) {
          head = item;
          head->next = NULL;
          head->prev = NULL;
       } else {
          tail->next = item;
          item->prev = tail;
       }
       tail = item;
    }

    AnsiString DeleteSpaces(AnsiString text)
    {
        int len = text.Length(), count = 0;
        AnsiString str;
        str.SetLength( len + 1 );

        for( int i=1; i<= len; i++)
        {
                if (text[i] != ' ')
                {
                        str[++count] = text[i];
                }
        }
        str[count+1] = 0;
        return str;
    }
};

//========================= TEST ======================================

bool Compare (int* array, int* result, int array_size, int result_size)
{
   if(result_size != array_size)
     return false;
   else
   {
     for (int j = 0; j < result_size; j++)
     {
          if(result[j] != array[j])
          {
               return false;
          }
     }
   }
   return true;
}

int test_OList()
{
   OrderedList<int>* OList = new OrderedList<int>(true);
   int test = 0;

   OList->Add(1);
   OList->Add(5);
   OList->Add(7);
   OList->Add(1);
   OList->Add(6);

   int list_size = OList->Count();          // get list_size
   int OListResult[5] = {1,1,5,6,7};        // get result array
   int* arrayINT = OList->GetAll();         // get OList array
   int* arrayResult = OListResult;
   int result_size = sizeof(OListResult)/sizeof(OListResult[0]);  //get result array size
   if( !Compare(arrayINT, arrayResult, list_size, result_size) ) test++;  // compare size and filling

   OList->Delete(6);
   OList->Delete(1);
   OList->Delete(7);

   list_size = OList->Count();
   int OListResult2[2] = {1,5};
   arrayINT = OList->GetAll();
   arrayResult = OListResult2;
   result_size = sizeof(OListResult2)/sizeof(OListResult2[0]);
   if( !Compare(arrayINT, arrayResult, list_size, result_size) ) test++;

   Node<int>* node = OList->Find(1);
   int value = node->value;
   if (value != 1) test++;

   node = OList->Find(5);
   value = node->value;
   if (value != 5) test++;

   OList->Clear(false);

   OList->Add(1);
   OList->Add(5);
   OList->Add(7);
   OList->Add(1);
   OList->Add(6);

   list_size = OList->Count();
   int OListResult3[5] = {7,6,5,1,1};
   arrayINT = OList->GetAll();
   arrayResult = OListResult3;
   result_size = sizeof(OListResult3)/sizeof(OListResult3[0]);
   if( !Compare(arrayINT, arrayResult, list_size, result_size) ) test++;

   OList->Delete(6);
   OList->Delete(1);
   OList->Delete(7);

   list_size = OList->Count();
   int OListResult4[2] = {5,1};
   arrayINT = OList->GetAll();
   arrayResult = OListResult4;
   result_size = sizeof(OListResult4)/sizeof(OListResult4[0]);
   if( !Compare(arrayINT, arrayResult, list_size, result_size) ) test++;

   node = OList->Find(1);
   value = node->value;
   if (value != 1) test++;

   node = OList->Find(5);
   value = node->value;
   if (value != 5) test++;

   //----------  visual check ----------
   OrderedList<String>* St_OList = new OrderedList<String>(true);
   St_OList->Add("А");
   St_OList->Add("АБ");
   St_OList->Add("А Б");

   St_OList->Clear(false);
   St_OList->Add("А");
   St_OList->Add("АБ");
   St_OList->Add("А Б");
   St_OList->Add(" АБAБ");
   St_OList->Delete("А Б");

   String* list2 = St_OList->GetAll();

   AnsiString S2 ="";
   int count2 = St_OList->Count();
   for (int i = 0; i < count2; i++)
   {
     S2 = S2 + " " + list2[i];
   }
   //Form1->MemoCHAR->Text = S2;
   delete St_OList;
   //----------------------------------

   delete OList;
   return test;
}

//---------------------------------------------------------------------------
#endif