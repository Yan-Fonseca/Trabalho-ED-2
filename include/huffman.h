#ifndef HUFFMAN_H
#define HUFFMAN_H

namespace heap {
    const int heapVectorSize = 256;

    class hNode {
        private:
            char value;
            int frequency;
        public:
            hNode(char key){
                this.value = key;
                this.frequency = 1;
            }
            ~hNode() { }

            int getFrequency() {
                return this->frequency;
            }

            char getValue() {
                return this->value;
            }

            void incrementFrequency() {
                this->frequency++;
            }
    }

    class Heap {
    private:
        hNode *heapVector;
        int heapSize;
    public:
        Heap() {
            this->heapSize = 0;
            this->heapVector = new hNode[heapVectorSize];
        }
        ~Heap() {
            delete [] this->heapVector;
        }


        int getHeapSize() {
            return this->heapSize;
        }

        hNode heapMax() {
            return this->heapVector[0];
        }

        int left(int index) {
            return index*2;
        }

        int right(int index) {
            return index*2 + 1;
        }

        void trocar(int index, int bigger) {
            hNode aux = this->heapVector[index];
            this->heapVector[index] = this->heapVector[bigger];
            this->heapVector[bigger] = aux;
        }
        
        void maxHeapify(int index) {
            int l = left(index);
            int r = right(index);
            int bigger;

            if(l <= this->heapSize && this->heapVector[l] > this->heapVector[index]) {
                bigger = l;
            }
            else {
                bigger = index;
            }

            if(r <= this->heapSize && this->heapVector[r] > this->heapVector[bigger]) {
                bigger = r;
            }

            if(maior != index) {
                trocar(index, bigger);
                maxHeapify(bigger);
            }
        }
    }
}

namespace huffman {
    
}

#endif