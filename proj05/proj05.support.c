int convert( int a, unsigned int b, char c[]){
    if(b < 2){
        return 0;
    }
    if(b > 36){
        return 0;        
    }

    int negative;
    
    if(a >= 0){
        negative = 0;
    }
    else{
        negative = 1;
        a = a * -1;
    }

    char array[34];
    
    array[0] = '\0';
    
    int it = 1;
    
    while(a >= b){
        char value;
        if(a%b < 10){
            value = a%b + '0';
        }
        else{
            value = ('A' + a%b ) - 10;
        }
        array[it] = value;
        a = a/b;
        it += 1;
    }
    char value1;
    if(a < 10){
        value1 = a + '0';
    }
    else{
        value1 = ('A' + a) - 10;
    }

    array[it] = value1;
    it += 1;
    if(negative == 1){
        array[it] = '-';
    }
    else{
        array[it] = '+';
    }
    
    int rev_it = 0;
    while(it >= 0){
        c[rev_it] = array[it];
        it -= 1;
        rev_it += 1;
    }

    return 1;
}

