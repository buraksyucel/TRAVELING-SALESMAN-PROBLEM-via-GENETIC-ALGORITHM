#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUMBER_OF_CITY 10
#define NUMBER_OF_POPULATION 20
#define COORDINATE_RANGE_END 20
#define MUTATION_RATE 0.5 // must be between 0 and 1  ex: 0.2
#define NEW_POPULATION 10 // NUMBER OF POPULATION/Z

void createCoordinates(int array[NUMBER_OF_CITY][2]){
	srand(time(NULL));
	for(int x=0 ; x<=NUMBER_OF_CITY-1 ; x++ ){
		
		for( int y=0 ; y<=NUMBER_OF_CITY-1 ; y++){
				
		array[x][y]=rand() %COORDINATE_RANGE_END;
		}
	}
}

void printCoordinates(int array[NUMBER_OF_CITY][2]){
	printf("X \t Y \n");
	
	for(int i=0 ; i<=NUMBER_OF_CITY-1;i++){
		for(int k=0; k<2; k++){
		printf("%d\t ", array[i][k]);
		}
	printf("\n");
		}
}

void createRootes(int array[NUMBER_OF_POPULATION][NUMBER_OF_CITY]){	
	srand(time(NULL));
	int i,counter=0;
	for(int r=0 ; r<NUMBER_OF_POPULATION ; r++){
		for(int z=0; z<NUMBER_OF_CITY;z++){
				
			int c=1+rand()%NUMBER_OF_CITY;
			for(i=0;i<z;i++){
				if(array[r][i]==c){
					z--;
					break;
				}
			}
			if(z==i){
				array[r][z]=c;
			}		
		}
		for(i=0;i<r;i++){
			counter=0;
			for(int z=0; z<NUMBER_OF_CITY;z++){
			if(array[i][z]==array[r][z]){
				counter++;
			}
			}
			if(counter==NUMBER_OF_CITY){
				r--;
				counter=0;
				break;	
			}
		}
		
	}
}

void printRootes(int array[NUMBER_OF_POPULATION][NUMBER_OF_CITY]){	
	for(int r=0 ; r<NUMBER_OF_POPULATION ; r++){
		
		printf("%d. Route =====> ",r+1);
		
		for(int z=0; z<NUMBER_OF_CITY;z++){
			
				printf("%d ",array[r][z]);
			}
		
		printf("\n");
	}
}

void calculateDistanceMatrix(float array[NUMBER_OF_CITY][NUMBER_OF_CITY],int cities[NUMBER_OF_CITY][2]){
	float X,Y,distance;
	for(int i=0;i<NUMBER_OF_CITY;i++){
		for(int j=0;j<NUMBER_OF_CITY;j++){
			X = cities[i][0] - cities[j][0];
			Y = cities[i][1] - cities[j][1];
			distance = sqrt(X*X + Y*Y);
			array[i][j] = distance;	
		}
	}
		
}

void printDistanceMatrix(float array[NUMBER_OF_CITY][NUMBER_OF_CITY]){
	for(int r=0 ; r<NUMBER_OF_CITY ; r++){		
		for(int z=0; z<NUMBER_OF_CITY;z++){
			printf("%.2f\t ",array[r][z]);
			}		
		printf("\n");
	}
		
}

void calculatePathDistance(float Distance[NUMBER_OF_CITY][NUMBER_OF_CITY],int routes[NUMBER_OF_POPULATION][NUMBER_OF_CITY],float totalDistance[NUMBER_OF_POPULATION]){
	float total = 0;
	for (int i=0; i<NUMBER_OF_POPULATION; i++){	
		for(int j=0; j<NUMBER_OF_CITY-1; j++){
		
		total = total + Distance[routes[i][j]-1][routes[i][j+1]-1];	
		}
		totalDistance[i]=total;
		total = 0;

	}	
}

void printPathDistance(float totalDistance[NUMBER_OF_POPULATION]){
	printf("\n");
	for (int i=0; i<NUMBER_OF_POPULATION; i++){		
		printf("Total distance of %d. route= %.2f\n",i+1,totalDistance[i]);

	}	
}

void createNewRoutes(int routes[NUMBER_OF_POPULATION][NUMBER_OF_CITY],int newroutes[NEW_POPULATION][NUMBER_OF_CITY]){
	int pathHolder[NEW_POPULATION];
	int k=0;
	int x,samePathNumber=0;
	srand(time(NULL));
	for(int i=0; i<NEW_POPULATION ; i++){
		x=rand()%NUMBER_OF_POPULATION ;
		pathHolder[i]=x;
		k=0;
		samePathNumber=0;
		for(k=0;k<i;k++){
			if(pathHolder[i]==pathHolder[k]){
				i--;
				samePathNumber=1;
				break;
			}
		}
		if(samePathNumber==0){
			for(int j=0 ; j<NUMBER_OF_CITY; j++){
				newroutes[i][j]=routes[pathHolder[i]][j];	
			}
		}
	}
}

void printNewRoutes(int newroutes[NEW_POPULATION][NUMBER_OF_CITY]){
	printf("\n");
	for(int r=0 ; r<NEW_POPULATION ; r++){
		printf("%d. Random Route =====> ",r+1);
		for(int z=0; z<NUMBER_OF_CITY;z++){
			printf("%d ",newroutes[r][z]);
		}
		printf("\n");
	}
		
}

void FindingNewRoutesDistance(float distanceMatrix[NUMBER_OF_CITY][NUMBER_OF_CITY], int newroutes[NEW_POPULATION][NUMBER_OF_CITY], float newroutesDistance[NEW_POPULATION]){
	float total = 0;
	for (int i=0; i<NEW_POPULATION; i++){
		total = 0;
		for(int j=0; j<NUMBER_OF_CITY-1; j++){
			total = total + distanceMatrix[newroutes[i][j]-1][newroutes[i][j+1]-1];	
		}
		newroutesDistance[i]=total;
		total=0;
	}		
}

void printNewRoutesDistance(float newroutesDistance[NEW_POPULATION]){
	for (int i=0; i<NEW_POPULATION; i++){		
		printf("Total distance of %d. Random Route= %.2f\n",i+1,newroutesDistance[i]);
	}	
}

void findingShortestCities(float newroutesDistance[NEW_POPULATION],int newroutes[NEW_POPULATION][NUMBER_OF_CITY],int shortest[2][NUMBER_OF_CITY]){
	//en küçük olarak ilk nokta ve þehir degerleri atandý
	float shortestone=newroutesDistance[0];
	for(int t=0;t<NUMBER_OF_CITY;t++){
		shortest[0][t]=newroutes[0][t];
	}
	//en küçük ikinci olarak ilk nokta ve þehir degerleri atandý
	float shortesttwo=newroutesDistance[0];
	for(int t=0;t<NUMBER_OF_CITY;t++){
		shortest[1][t]=newroutes[0][t];
	}
	
	for(int s=0 ; s<NEW_POPULATION ; s++){
		if(newroutesDistance[s]<=shortestone){
			shortestone=newroutesDistance[s];
			for(int t=0;t<NUMBER_OF_CITY;t++){
				shortest[0][t]=newroutes[s][t];
			}
			
		}
		else if(newroutesDistance[s]<=shortesttwo){
			shortesttwo=newroutesDistance[s];
			for(int t=0;t<NUMBER_OF_CITY;t++){
				shortest[1][t]=newroutes[s][t];
			}
		}
	}
}

void printShortestCities(int shortest[2][NUMBER_OF_CITY]){
	printf("\nThe shortest routes are\n");	
	for(int i=0;i<NUMBER_OF_CITY;i++){
		printf("%d ",shortest[0][i]);
	}
	printf("\n");

	for(int j=0;j<NUMBER_OF_CITY;j++){
		printf("%d ",shortest[1][j]);
	}
	printf("\n");	
}

void calculateShortestDistance(int shortest[2][NUMBER_OF_CITY],float distanceMatrix[NUMBER_OF_CITY][NUMBER_OF_CITY],float shortestDistance[2]){
	float total = 0;
	
	for (int i=0; i<2; i++){	
		for(int j=0; j<NUMBER_OF_CITY-1; j++){
			
			total = total + distanceMatrix[shortest[i][j]-1][shortest[i][j+1]-1];	
		}
		shortestDistance[i]=total;
		total = 0;

	}	
	
}

void printShortestnDistance(float shortestDistance[2]){
	printf("\n");
	for (int i=0; i<2; i++){		
		printf("Total distance of %d. shortest city= %.2f\n",i+1,shortestDistance[i]);

	}
	printf("\n");
}

void generateCrossover(int shortest[2][NUMBER_OF_CITY],int crossover[2][NUMBER_OF_CITY]){
srand(time(NULL));
int cop=1+rand()%(NUMBER_OF_CITY-1);
printf("The crossover point :  %d\n",cop);	
int temp=0;

for(int i=0 ; i<NUMBER_OF_CITY ; i++){
	crossover[0][i]=shortest[0][i];
	crossover[1][i]=shortest[1][i];
}
	
for(int i=cop ; i<NUMBER_OF_CITY ; i++){
	temp=crossover[0][i];
	crossover[0][i]	=crossover[1][i];
	crossover[1][i]=temp;
}
for(int j=0 ; j<NUMBER_OF_CITY ; j++){
	for(int i=0 ; i<j ; i++){
		if(crossover[0][i]==crossover[0][j]){
			crossover[0][j]=1+rand()%NUMBER_OF_CITY;
			j--;	
		}
	
	}
}
for(int j=0 ; j<NUMBER_OF_CITY ; j++){
	for(int i=0 ; i<j ; i++){
		if(crossover[1][i]==crossover[1][j]){
			crossover[1][j]=1+rand()%NUMBER_OF_CITY;
			j--;	
		}
	
	}
}
	
}
void printCrossover(int crossover[2][NUMBER_OF_CITY]){
	printf("The crossover routes are\n\n");	
	for(int i=0;i<NUMBER_OF_CITY;i++){
		printf("%d ",crossover[0][i]);
	}
	printf("\n");

	for(int i=0;i<NUMBER_OF_CITY;i++){
		printf("%d ",crossover[1][i]);
	}
	printf("\n");	
}
void generateMutasyon(int crossover[2][NUMBER_OF_CITY],int mutasyon[2][NUMBER_OF_CITY]){
	int mutasyonRate=1/MUTATION_RATE;
	int mutasyonProb=rand()%mutasyonRate;
	int mp[2];
	int temp=0;
	
	for(int i=0 ; i<2 ; i++){
		mp[i]=1+rand()%(NUMBER_OF_CITY-1);
		for(int j=0 ; j<i ; j++){
			if(mp[i]==mp[j]){
				i--;
				break;
			}		
		}
	}
	
	for(int i=0 ; i<NUMBER_OF_CITY ; i++){
		mutasyon[0][i]=crossover[0][i];
		mutasyon[1][i]=crossover[1][i];
	}
	
	if(mutasyonProb==0){
		printf("\nmutasyon gerceklesti\n");
		temp=mutasyon[0][mp[0]];
		mutasyon[0][mp[0]]=mutasyon[0][mp[1]];
		mutasyon[0][mp[1]]=temp;
		
		temp=mutasyon[1][mp[0]];
		mutasyon[1][mp[0]]=mutasyon[1][mp[1]];
		mutasyon[1][mp[1]]=temp;
	}
	else {
		printf("\nmutasyon gerceklesmedi\n");
	}
}
void printMutasyon(int mutasyon[2][NUMBER_OF_CITY]){
	printf("\n");
	for(int i=0;i<NUMBER_OF_CITY;i++){
		printf("%d ",mutasyon[0][i]);
	}
	printf("\n");

	for(int i=0;i<NUMBER_OF_CITY;i++){
		printf("%d ",mutasyon[1][i]);
	}
	printf("\n");
}

void calculateMutasyonDistance(int mutasyon[2][NUMBER_OF_CITY],float distanceMatrix[NUMBER_OF_CITY][NUMBER_OF_CITY],float mutasyonDistance[2]){
	float total = 0;
	for (int i=0; i<2; i++){	
		for(int j=0; j<NUMBER_OF_CITY-1; j++){
		
		total = total + distanceMatrix[mutasyon[i][j]-1][mutasyon[i][j+1]-1];	
		}
		mutasyonDistance[i]=total;
		total = 0;

	}	
}

void printMutasyonDistance(float mutasyonDistance[2]){
	printf("\n");
	for (int i=0; i<2; i++){		
		printf("Total distance of %d. mutasyon= %.2f\n",i+1,mutasyonDistance[i]);

	}
	printf("\n");
}

void replacing(int mutasyon[2][NUMBER_OF_CITY],float shortestDistance[2],float mutasyonDistance[2],int routes[NUMBER_OF_POPULATION][NUMBER_OF_CITY], int biggest[1]){
	int smallest=0;
	if(mutasyonDistance[1]<mutasyonDistance[0]){
		smallest=1;
	}
	if(shortestDistance[1]>mutasyonDistance[smallest]){
		for(int i=0;i<NUMBER_OF_CITY;i++){
			routes[biggest[0]][i]=mutasyon[smallest][i];
		}
		
	}
}

void findingBiggestRoute(float totalDistance[NUMBER_OF_POPULATION],int biggest[1]){
	float biggestRoute=totalDistance[0];
	biggest[0]=0;
	for(int i=0;i<NUMBER_OF_POPULATION;i++){
		if(biggestRoute<totalDistance[i]){
			biggestRoute=totalDistance[i];
			biggest[0]=i;
			
		}		
	}
	//printf("%d is the biggest route\n",biggest[0] + 1);
}

void pritingResult(int shortest[2][NUMBER_OF_CITY]){
	printf("\n\n\n\n\nThe shortest two routes are\n");
	for(int i=0;i<2;i++){
		printf("%d. smallest route===>  ",i+1);
		for(int j=0;j<NUMBER_OF_CITY;j++){
		printf("%d  ",shortest[i][j]);
		}
		printf("\n");
	}
}

int main(){
	
	int cities[NUMBER_OF_CITY][2];
	int routes[NUMBER_OF_POPULATION][NUMBER_OF_CITY];
	float distanceMatrix[NUMBER_OF_CITY][NUMBER_OF_CITY];
	float totalDistance[NUMBER_OF_POPULATION];
	int newroutes[NEW_POPULATION][NUMBER_OF_CITY];
	float newroutesDistance[NEW_POPULATION];
	int shortest[2][NUMBER_OF_CITY];
	int biggest[1];
	float shortestDistance[2];
	int crossover[2][NUMBER_OF_CITY];
	int mutasyon[2][NUMBER_OF_CITY];
	float mutasyonDistance[2];
	
	
	createCoordinates(cities);
	printCoordinates(cities);
	
	calculateDistanceMatrix(distanceMatrix,cities);
	printDistanceMatrix(distanceMatrix);
	
	createRootes(routes);
	printRootes(routes);
	
	do{
		calculatePathDistance(distanceMatrix,routes,totalDistance);
		printPathDistance(totalDistance);
		
		createNewRoutes(routes,newroutes);
		printNewRoutes(newroutes);
	
		FindingNewRoutesDistance(distanceMatrix,newroutes,newroutesDistance);
		printNewRoutesDistance(newroutesDistance);
		
		findingShortestCities(newroutesDistance,newroutes,shortest);
		printShortestCities(shortest);
	
		calculateShortestDistance(shortest,distanceMatrix,shortestDistance);
		printShortestnDistance(shortestDistance);
		
		generateCrossover(shortest,crossover);
		printCrossover(crossover);
		
		generateMutasyon(crossover,mutasyon);
		printMutasyon(mutasyon);
		
		calculateMutasyonDistance(mutasyon,distanceMatrix,mutasyonDistance);
		printMutasyonDistance(mutasyonDistance);
		
		findingBiggestRoute(totalDistance,biggest);
		replacing(mutasyon,shortestDistance,mutasyonDistance,routes,biggest);
		
	}while( totalDistance[biggest[0]] - int(shortestDistance[0]) > 1);
	pritingResult(shortest);
		
}
