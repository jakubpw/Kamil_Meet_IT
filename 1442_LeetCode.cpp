int countTriplets(vector<int>& arr) {
    int ans = 0;
    for(int i = 0; i<arr.size()-1; i++){
        int a = arr[i];
        for(int j = i+1; j<arr.size(); j++){
            a^=arr[j];
            if(a==0){
                ans+=j-i;
            }
        }
    }
    return ans;
}
