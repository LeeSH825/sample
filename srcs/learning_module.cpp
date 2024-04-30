class Learning_Module {
	private:
		char learning_Table[100];
	public:
		int calcWeight(int pre_spike_table[3], int post_spike_table[3]);
};

int Learning_Module::calcWeight(int pre_sike_table[3], int post_spike_table[3]){
	int new_weight = 1;
	for(int i=0; i<3; i++) {
		for (int j=0; j < 3; j++){
			new_weight *= pre_sike_table[i] * post_spike_table[j];
		}
	}
	return new_weight;
}