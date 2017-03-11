int total_subsequence_under_K (int K){
    deque < pair < int, int > > qmax, qmin;
    int L = 0, R = 0, ans = 0;
    while(L < N && R < N){
        while(!qmin.empty() && qmin.front().second < L){
            qmin.pop_front();
        }
        while(!qmax.empty() && qmax.front().second < L){
            qmax.pop_front();
        }
        if (L==R || max(qmax.front().first, ori[R]) - min(qmin.front().first, ori[R]) <= K){
            ans += R-L+1;
            while(!qmin.empty() && qmin.back().first >= ori[R])
                qmin.pop_back();
            while(!qmax.empty() && qmax.back().first <= ori[R])
                qmax.pop_back();
            qmin.push_back({ori[R],R});
            qmax.push_back({ori[R],R});
            R++;
        }
        else {
            L++;
        }
    }
    return ans;
}
