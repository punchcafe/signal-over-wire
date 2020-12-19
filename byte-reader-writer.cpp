#define HIGHVOLT 1
#define LOWVOLT 0

#define INDEX1 0x01
#define INDEX2 0x03
#define INDEX3 0b01

#include <stdio.h>
#include <assert.h> 


class ByteReader
{
    public:

    void reset(){
        this->byteResult = 0x00;
        this->byteloadIndex = 0;
    }

    int getIntValue()
    {
        return (int) this->byteResult;
    }

    char getCharValue()
    {
        return (char) this->byteResult;
    }

    bool readBit(bool isHigh)
    {
        if(this->byteloadIndex >= 7)
        {
            return false;
        }

        if(isHigh)
        {
            unsigned char currentChar = this->getCharForIndex(this->byteloadIndex);
            this->byteResult = this->byteResult | currentChar;
        }
        this->byteloadIndex++;
        if(this->byteloadIndex >= 7){
            return false;
        } else {
            return true;
        }
    }

    private:
    unsigned char byteResult;
    short byteloadIndex;

    unsigned char getCharForIndex(int index){
        // Return the char  coresponding to a single 1 at that index, i.e.:
        // getCharForIndex(2) -> 0b00000100
        assert(index >= 0);
        unsigned int roof = 0b10000000;
        int timesToFloorDivide = 7 - index;
        for(int i = 0; i < timesToFloorDivide; i++){
            roof = roof/2;
        }
        return roof;
    }


};

class ByteWriter
{
    public:

    void loadChar(unsigned char newCharToSend){
        this->charToSend = newCharToSend;
        this->sendingIndex = 0;
    }

    // returns true if has loaded bit, false if byte has been traversed
    bool loadNextBit(){
        if(this->sendingIndex >= 7){
            return false;
        }
        int sendingVal = (int) this->charToSend;
        int floorDividedVal = sendingVal;
        for(int i = 0; i < this->timesToFloorDivide(); i++){
            floorDividedVal = floorDividedVal / 2;
        }
        this->nextBit = (floorDividedVal % 2) == 1;

        this->sendingIndex++;
        return true;
    }

    bool getBit(){
        return this->nextBit;
    }

    private:

    unsigned char charToSend;
    bool nextBit;
    short sendingIndex;

    int timesToFloorDivide(){
        // -1 to offset so that we don't floor divide the number we need to modulo on.
        return 7 - this->sendingIndex - 1;
    }
};

void print_bool(bool b){
    if(b){
        printf("true\n");
    } else {
        printf("false\n");
    }
}

void print_bin(bool b){
    if(b){
        printf("1");
    } else {
        printf("0");
    }
}

int main()
{

    // Reading

    // testing functionality
    ByteReader br = ByteReader();
    // 0b0000101 -> the number 5
    br.reset();
    br.readBit(true);
    br.readBit(false);
    br.readBit(true);
    // printf("%d", br.getIntValue());
    printf("%d", br.getIntValue());

    // 0b1100011 -> the character 'c'
    br.reset();
    br.readBit(true);
    br.readBit(true);
    br.readBit(false);
    br.readBit(false);
    br.readBit(false);
    bool hasMore1 = br.readBit(true);
    bool hasMore2 = br.readBit(true);
    assert(hasMore1);
    assert(!hasMore2);
    printf("%c", br.getCharValue());

    // Writing
    ByteWriter bw = ByteWriter();
    bw.loadChar('c');
    bool result [8];
    bool hasNext [8];
    result[0] = bw.getBit();   
    hasNext[0] = bw.loadNextBit();
    result[1] = bw.getBit();   
    hasNext[1] = bw.loadNextBit();    
    result[2] = bw.getBit();   
    hasNext[2] = bw.loadNextBit();
    result[3] = bw.getBit();   
    hasNext[3] = bw.loadNextBit();
    result[4] = bw.getBit();   
    hasNext[4] = bw.loadNextBit();
    result[5] = bw.getBit();   
    hasNext[5] = bw.loadNextBit();
    result[6] =  bw.getBit();   
    hasNext[6] = bw.loadNextBit();
    result[7] = bw.getBit();   
    hasNext[7] = bw.loadNextBit();

    printf("bin:\n");
    for(int i = 0; i< 8; i++){
        print_bin(result[i]);
    }

    for(int i = 0; i< 8; i++){
        print_bool(hasNext[i]);
    }
}