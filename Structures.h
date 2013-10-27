struct Person {
	int PERSONAL_ID;
	int PACKAGE_WEIGHT;
};

// Get next working wicket
int getNextWorking(int *w, int dim, int current) {
	int i;
	
	for(i=current+1; i<dim; i++) {
		if(w[i] == 1) {
			return i;
		}
	}
	for(i=0; i<current; i++) {
		if(w[i] == 1) {
			return i;
		}
	}
}
