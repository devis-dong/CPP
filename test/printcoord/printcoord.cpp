/*** 
 * @Author: devis dong
 * @Date: 2021-07-17 10:04:30
 * @LastEditTime: 2021-07-18 16:26:59
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\test\printcoord\printcoord.cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <initializer_list>
#include "dswatch.h"

using namespace std;
using namespace ds;

void printcoord(const vector<int>& p)
{
    cout<<"(";
    for(int i = 0; i < p.size(); ++i)
    {
        cout<<p[i]<<",";
    }
    cout<<")"<<endl;
}

void printcoord_c(int* p, int dims)
{
    cout<<"(";
    for(int i = 0; i < dims-1; ++i)
    {
        cout<<p[i]<<",";
    }
    cout<<p[dims-1]<<")";
}

bool equal(vector<int>& p0, vector<int>& p1)
{
    // assert (p0.size() == p1.size());
    for(int i = 0; i < p0.size(); ++i)
    {
        if(p0[i] != p1[i]) return false;
    }
    return true;
}

bool move2next(vector<int>& p, const vector<int>& start, const vector<int>& step, const vector<int>& end)
{
    for(int i = p.size()-1; i >= 0; --i)
    {
        // assert ((start[i] <= p[i] && p[i] <= end[i]) || (end[i] <= p[i] && p[i] <= start[i]));
        if(end[i] != p[i])
        {
            p[i] += step[i];
            return true;
        }
        else
        {
            p[i] = start[i];
        }
    }
    return false;
}

bool move2next_c(int* p, int* start, int* step, int* end, const int n)
{
    for(int i = n-1; i >= 0; --i)
    {
        p[i] += step[i];
        // assert ((start[i] <= p[i] && p[i] <= end[i]) || (end[i] <= p[i] && p[i] <= start[i]));
        if(end[i] != p[i])
        {
            return true;
        }
        else
        {
            p[i] = start[i];
        }
    }
    return false;
}

vector<int> get_step(const vector<int>& start, const vector<int>& end)
{
    assert (start.size() == end.size());
    vector<int> step(start.size());
    for(int i = 0; i < step.size(); ++i)
    {
        step[i] = start[i] < end[i] ? 1 : -1;
    }
    return step;
}

int get_step_c(int* start, int* end, int* step, int n)
{
    for(int i = 0; i < n; ++i)
    {
        step[i] = start[i] < end[i] ? 1 : -1;
    }
    return 0;
}

double printrange(vector<int>& start, vector<int>& end)
{
    Watch mywatch;
    mywatch.start_clock();
    assert (start.size() == end.size());
    vector<int> step = get_step(start, end);
    vector<int> p = start;
    do
    {
        // printcoord(p);
    }while(move2next(p, start, step, end));
    mywatch.stop_clock();
    return mywatch.get_duration();
}

double printrange_c(vector<int>& start, vector<int>& end)
{
    Watch mywatch;
    mywatch.start_clock();
    int pstep[32], p[32], n = start.size();
    int *pstart = &start[0], *pend = &end[0];
    memcpy(p, start.data(), n*sizeof(int));
    get_step_c(pstart, pend, pstep, n);
    do
    {
        // printcoord(p);
    }while(move2next_c(p, pstart, pstep, pend, n));
    mywatch.stop_clock();
    return mywatch.get_duration();
}

void coord_add(int* coor0, int* coor1, int* coor2, int dims)
{
    for(int i = 0; i < dims; ++i)
    {
        coor2[i] = coor0[i] + coor1[i];
    }
}

void coord_add_one(int* coord, int dims)
{
    for(int i = 0; i < dims; ++i)
    {
        coord[i] += 1;
    }
}

void coord_sub(int* coor0, int* coor1, int* coor2, int dims)
{
    for(int i = 0; i < dims; ++i)
    {
        coor2[i] = coor0[i] - coor1[i];
    }
}

void coord_sub_one(int* coord, int dims)
{
    for(int i = 0; i < dims; ++i)
    {
        coord[i] -= 1;
    }
}

int coord2idx(int* p, int* shape, int dims)
{
    int idx = 0, interval = 1;
    for(int i = dims-1; i >= 0; --i)
    {
        idx += interval * p[i];
        interval *= shape[i];
    }
    return idx;
}

void idx2coord(int idx, int* coord, int* shape, int dims)
{
    for(int i = dims-1; i >= 0; --i)
    {
        coord[i] = idx % shape[i];
        idx /= shape[i];
    }
}

template <typename T>
T* multiply(T* mat, int* p, T* mask, int* q, int* shape_mat, int* shape_mask, int dims)
{
    int idx_mat = coord2idx(p, shape_mat, dims);
    int idx_mask = coord2idx(q, shape_mask, dims);
    return mat[idx_mat]*mask[idx_mask];
}

int get_len(int* shape, int dims)
{
    int len = 1;
    for(int i = dims-1; i >= 0; --i)
    {
        len *= shape[i];
    }
    return len;
}

template <typename T>
double sumproduct(T* mat, int* shape_mat, T* mask, int* shape_mask, int dims, int* offset=nullptr)
{
    int pstart[64] = {0}, pend[64] = {0}, p[64] = {0}, pstep[64] = {0};
    if(nullptr != offset) coord_add(pstart, offset, pstart, dims);
    coord_add(pstart, shape_mask, pend, dims);
    memcpy(p, pstart, dims*sizeof(int));
    get_step_c(pstart, pend, pstep, dims);
    int klen = get_len(shape_mask, dims);
    double sum = 0;
    int i = -1, j = -1;
    // printcoord_c(pstart, dims);
    // printcoord_c(pend, dims);
    // printcoord_c(pstep, dims);
    do
    {
        ++i;
        j = coord2idx(p, shape_mat, dims);
        sum += mat[j]*mask[i];
        // printcoord_c(p, dims);
    }while(move2next_c(p, pstart, pstep, pend, dims) && i < klen);
    return sum;
}

template <typename T>
void get_convoled_shape(T* mat, int* shape_mat, T* ker, int* shape_ker, int* step, int* shape_con, int dims)
{
    for(int i = 0; i < dims; ++i)
    {
        shape_con[i] = (shape_mat[i] - shape_ker[i])/step[i] + 1;
    }
}

template <typename T>
int conv(T* mat, int* shape_mat, T* ker, int* shape_ker, int* step, T* con, T* shape_con, int dims)
{
    int offset[64] = {0}, start[64] = {0}, end[64] = {0};
    coord_sub(shape_mat, shape_ker, end, dims);
    coord_add_one(end, dims);
    get_convoled_shape(mat, shape_mat, ker, shape_ker, step, shape_con, dims);
    int len_con = get_len(shape_con, dims);
    int idx = 0;
    do
    {
        con[idx] = sumproduct(mat, shape_mat, ker, shape_ker, dims, offset);
    }while(move2next_c(offset, start, step, end, dims) && idx++ < len_con);
    return 0;
}

template <typename T>
void printmat(T* mat, int* shape, int dims)
{
    cout<<"shape: ";
    for(int i = 0; i < dims-1; ++i)
    {
        cout<<shape[i]<<"x";
    }
    cout<<shape[dims-1]<<endl;
    int n = get_len(shape, dims);
    int coord[64] = {0};
    for(int i = 0; i < n; ++i)
    {
        idx2coord(i, coord, shape, dims);
        printcoord_c(coord, dims);
        cout<<": "<<mat[i]<<endl;
    }
}

#define dims_num 3

int main()
{
    cout<<"running..."<<endl;
    int shape_mat[dims_num] = {1024, 1024, 3};
    int shape_ker[dims_num] = {3, 3, 3};
    int shape_con[dims_num] = {0};
    int step[dims_num] = {3, 3, 1};
    int len_mat = get_len(shape_mat, dims_num), len_ker = get_len(shape_ker, dims_num);
    int* mat = new int[len_mat];
    int* ker = new int[len_ker];
    get_convoled_shape(mat, shape_mat, ker, shape_ker, step, shape_con, dims_num);
    int len_con = get_len(shape_con, dims_num);
    int* con = new int[len_con];
    for(int i = 0; i < len_mat; ++i) mat[i] = 1;
    for(int i = 0; i < len_ker; ++i) ker[i] = 1;
    // vector<int> start = {0, 0, 0}, end = {1000, 1000, 1};
    // cout<<"time cost: "<<printrange(start, end)<<"s"<<endl;
    // cout<<"time cost: "<<printrange_c(start, end)<<"s"<<endl;
    Watch mywatch;
    mywatch.start_clock();
    conv(mat, shape_mat, ker, shape_ker, step, con, shape_con, dims_num);
    // double sum = sumproduct(mat, shape_mat, ker, shape_ker, dims_num);
    mywatch.stop_clock();
    // cout<<"sum: "<<sum<<endl;
    // printmat(con, shape_con, dims_num);
    cout<<"time cost: "<<mywatch.get_duration()<<"s"<<" frame rate:"<<1/mywatch.get_duration()<<endl;
    delete[] mat;
    delete[] ker;
    delete[] con;
    cout<<"...done."<<endl;
    system("pause");
    return 0;
}
