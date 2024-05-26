void debug(char lake[MAX][MAX], vector<vector<CD>> &unions){
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            cout<<lake[r][c];
        }cout<<"\n";
    }cout<<"\n";
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            CD cur(r,c);
            CD rep = unions[cur.row][cur.col].row!=-1 ? findRep(unions,cur) : CD(-1,-1);
            cout<<"("<<(rep.row==-1?"-":to_string(rep.row))<<","<<(rep.col==-1?"-":to_string(rep.col))<<")";
        }cout<<"\n";
    }cout<<"==================================================\n";
}
void debug2(list<CD> &reps,vector<vector<CD>> unions, vector<vector<vector<CD>>> &unionConnections){
    for(list<CD>::iterator it = reps.begin(); it != reps.end(); it++){
        CD &rep = *it;
        if(!(findRep(unions,rep)==rep)){
            it=reps.erase(it);
            it--;
            continue;
        }
        cout<<"("<<rep.row<<","<<rep.col<<"): ";
        vector<CD> &connections = unionConnections[rep.row][rep.col];
        for(int i = 0; i < connections.size(); i++){
            cout<<"("<<connections[i].row<<","<<connections[i].col<<") ";
        }
        cout<<"\n";
    }cout<<"==================================================\n";
}

void debug(char lake[MAX][MAX], vector<vector<CD>> &unions){
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            cout<<lake[r][c];
        }cout<<"\n";
    }cout<<"\n";
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            CD cur(r,c);
            CD rep = unions[cur.row][cur.col].row!=-1 ? findRep(unions,cur) : CD(-1,-1);
            cout<<"("<<(rep.row==-1?"-":to_string(rep.row))<<","<<(rep.col==-1?"-":to_string(rep.col))<<")";
        }cout<<"\n";
    }cout<<"==================================================\n";
}
void debug2(list<CD> &reps,vector<vector<CD>> unions, vector<vector<list<CD>>> &unionConnections){
    for(list<CD>::iterator it = reps.begin(); it != reps.end(); it++){
        CD &rep = *it;
        if(!(findRep(unions,rep)==rep)){
            it=reps.erase(it);
            it--;
            continue;
        }
        cout<<"("<<rep.row<<","<<rep.col<<"): ";
        list<CD> &connections = unionConnections[rep.row][rep.col];
        for(list<CD>::iterator it = connections.begin(); it != connections.end(); it++){
            cout<<"("<<it->row<<","<<it->col<<") ";
        }
        cout<<"\n";
    }cout<<"==================================================\n";
}