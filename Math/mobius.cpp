// Mobius
//

int mob[ms], np[ms];
 
void sieve(){
  memset(mob, -1, sizeof mob);
  for(int i=2; i<ms; i++){
    if(!np[i]){
      for(int j=i; j<ms; j+= i){
        mob[j] *= -1;
        np[j] = 1; 
        if((j/i)%i == 0) mob[j] = 0;
      }
    }
  }
}