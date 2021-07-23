/*** 
 * @Author: devis dong
 * @Date: 2021-07-21 13:05:23
 * @LastEditTime: 2021-07-23 16:06:12
 * @LastEditors: devis dong
 * @Description: 
 * @FilePath: \C++\src\dssift\dssift.cpp
 */

#include "dssift.h"
#include "dswatch.h"
#include "dslogger.h"


namespace ds
{
    Watch mywatch;
    logger(Logger::target_all, Logger::level_all, "sift.log");
 
    void get_sift_features(I Image& img_ori, O vector<KeyPoint>& feats, I const int intvs, I const double sigma, I const double contr_thr, I const double curv_thr, I const int upsample, I const int ori_hist_bins, I const int descr_win_width, I const int descr_hist_bins)
    {
        Image img_gray;
        create_init_smooth_gray(img_ori, img_gray, sigma, upsample);
        // show_image(img_gray, "gray");
        loginfo("step 1: building gaussian pyramid.");
        mywatch.start_clock();
        Pyramid gauss_pyr;
        gauss_pyr.octvs = log2(min(img_gray._h, img_gray._w))-3;
        gauss_pyr.intvs = intvs+3;
        gauss_pyr.imgs = new Image[gauss_pyr.octvs*gauss_pyr.intvs];
        assert (nullptr != gauss_pyr.imgs);
        create_gauss_pyramid(img_gray, gauss_pyr, sigma);
        mywatch.stop_clock();
        loginfo("step 1 time cost: %fs.", mywatch.get_duration());

        loginfo("step 2: building difference of gaussian pyramid.");
        mywatch.start_clock();
        Pyramid diff_pyr;
        diff_pyr.octvs = gauss_pyr.octvs;
        diff_pyr.intvs = gauss_pyr.intvs-1;
        diff_pyr.imgs = new Image[diff_pyr.octvs*diff_pyr.intvs];
        create_diff_pyramid(gauss_pyr, diff_pyr);
        mywatch.stop_clock();
        loginfo("step 2 time cost: %fs.", mywatch.get_duration());

        loginfo("step 3: detect the local extrema of the dog.");
        mywatch.start_clock();
        vector<KeyPoint> extrema;
        detect_local_extrema(diff_pyr, contr_thr, curv_thr, extrema);
        calculate_scale(extrema, sigma, diff_pyr.intvs);
        if(upsample) downsize_feats(extrema);
        mywatch.stop_clock();
        loginfo("step 3 time cost: %fs.", mywatch.get_duration());

        loginfo("step 4: intially generate keypoints.");
        mywatch.start_clock();
        assign_orient(gauss_pyr, extrema, ori_hist_bins, feats);
        mywatch.stop_clock();
        loginfo("step 4 time cost: %fs.", mywatch.get_duration());

        loginfo("step 5: generate descriptor for each keypoint.");
        mywatch.start_clock();
        generate_descriptor(feats, gauss_pyr, SIFT_DESCR_HIST_BINS, SIFT_DESCR_WINDOW_WIDTH);
        mywatch.stop_clock();
        loginfo("step 5 time cost: %fs.", mywatch.get_duration());

        loginfo("sift done.");
        delete[] gauss_pyr.imgs;
        delete[] diff_pyr.imgs;

    }

 
    int create_init_smooth_gray(I Image &src, O Image &dst, I double sigma, I const int upsample)
    {
        if(1 != src._c)
        {
            if(3 != src._c) return -1;
            bgr2gray(src, dst);
        }
        else
        {
            dst = src;
        }

        if(upsample)
        {
            double rate[3] = {2.0, 2.0, 1.0};
            dst = sample_image(dst, rate);
        }

        sigma = sqrt(sigma * sigma - (INIT_SIGMA * INIT_SIGMA)); //[1]-1层的sigma  
        int ker_shape[3] = {int(ceil(6*sigma + 1))/2*2 + 1, int(ceil(6*sigma + 1))/2*2 + 1, 1};
        dst = gaussian_blur(dst, ker_shape, sigma);
        return 0;
    }
    //  
    // vector<vector<Image>> create_gauss_pyramid(I Image& img, I const int octvs, I const int intvs, I const double sigma)
    // {
    //     vector<vector<Image>> pyr(octvs);
    //     double sample_rate[3] = {0.5, 0.5, 1};
    //     Image<double> ker, B;
    //     int ker_shape[3] = {int(6*sigma+1.5)/2*2+1, int(6*sigma+1.5)/2*2+1, 1};
    //     int step[3] = {1, 1, 1};
    //     int h = img._h/sample_rate[0], w = img._w/sample_rate[1], c = img._c/sample_rate[2];
    //     for(int i = 0; i < octvs; ++i)
    //     {
    //         pyr[i].resize(intvs+3);
    //         // ker = generate_gaussian_mat<double>(ker_shape, sigma*pow(2, i), true);
    //         // h *= sample_rate[0]; w *= sample_rate[1]; c *= sample_rate[2];
    //         // int pad_size[3] = {int(0.5*((h-1)*step[0]+ker_shape[0]-h)), int(0.5*((w-1)*step[1]+ker_shape[1]-w)), int(0.5*((c-1)*step[2]+ker_shape[2]-c))};
    //         // double k = pow(2.0, 1.0/double(intvs)), a = 0.5/(PI*sigma*sigma*pow(2, 2*i));
    //         // B = (a*k)/ker;
    //         // B *= B;
    //         for(int j = 0; j < intvs+3; ++j)
    //         {
    //             if(0 == i && 0 == j)
    //             {
    //                 pyr[i][j] = img;
    //             }
    //             else if(0 == j)
    //             {
    //                 pyr[i][j] = sample_image(pyr[i-1][intvs], sample_rate);
    //             }
    //             else
    //             {
    //                 // ker *= B;
    //                 // pyr[i][j] = convolve<double, double, double>(pyr[i][j-1], ker, step, pad_size);
    //                 pyr[i][j] = gaussian_blur(pyr[i][j-1], ker_shape, sigma*pow(2, i+j/intvs));
    //             }
    //         }
    //     }
    //     return pyr;
    // }

 
    void create_gauss_pyramid(I Image& img, I O Pyramid& pyr, I const double sigma)
    {
        assert (pyr.intvs >= 3);
        double sample_rate[3] = {0.5, 0.5, 1};
        int ker_shape[3] = {int(ceil(6*sigma+1))/2*2+1, int(ceil(6*sigma+1))/2*2+1, 1};
        int step[3] = {1, 1, 1};
        int h = img._h/sample_rate[0], w = img._w/sample_rate[1], c = img._c/sample_rate[2];
        for(int i = 0, idx = 0; i < pyr.octvs; ++i)
        {
            for(int j = 0; j < pyr.intvs; ++j, ++idx)
            {
                if(0 == i && 0 == j)
                {
                    pyr.imgs[idx] = img;
                }
                else if(0 == j)
                {
                    pyr.imgs[idx] = sample_image(pyr.imgs[i*pyr.intvs-3], sample_rate);
                }
                else
                {
                    pyr.imgs[idx] = gaussian_blur(pyr.imgs[idx-1], ker_shape, sigma*pow(2, i+j/pyr.intvs));
                }
            }
        }
    }

 
    void create_diff_pyramid(I const Pyramid& gauss_pyr, I O Pyramid& diff_pyr)
    {
        assert (diff_pyr.octvs == gauss_pyr.octvs && diff_pyr.intvs == gauss_pyr.intvs-1);
        for(int i = 0, id = 0, ig = 0; i < diff_pyr.octvs; ++i, ++ig)
        {
            for(int j = 0; j < diff_pyr.intvs; ++j, ++id, ++ig)
            {
                diff_pyr.imgs[id] = gauss_pyr.imgs[ig+1] - gauss_pyr.imgs[ig];
            }
        }
    }

 
    bool is_extremum(I const Pyramid& pyr, I const int octv, I const int intv, I const int y, I const int x)
    {
        Image *pimg_m = pyr.imgs + octv*pyr.intvs+intv;
        Image *pimg_l = pyr.imgs + octv*pyr.intvs+intv-1;
        Image *pimg_r = pyr.imgs + octv*pyr.intvs+intv+1;
        double val = pimg_m->at(y, x);
        bool flag = true;
        for(int i = y-1; i <= y+1; ++i)
        {
            for(int j = x-1; j <= x+1; ++j)
            {
                if(val < pimg_m->at(i, j) || val < pimg_l->at(i, j) || val < pimg_r->at(i, j))
                {
                    if(y-1 == i && x-1 == j)
                    {
                        flag = false;
                        break;
                    }
                    return false;
                    // flag = false;
                    // break;
                }
            }
        }

        if(flag) return true;

        for(int i = y-1; i <= y+1; ++i)
        {
            for(int j = x-1; j <= x+1; ++j)
            {
                if(val > pimg_m->at(i, j) || val > pimg_l->at(i, j) || val > pimg_r->at(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }

 
    void detect_local_extrema(I const Pyramid& pyr, I const double contr_thr, I const int curv_thr, O vector<KeyPoint>& keypoints)
    {
        int cnt0 = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0;
        double  thresh = 0.5 * contr_thr / SIFT_INTVS;
        KeyPoint tmp;
        for(int i = 0; i < pyr.octvs; ++i)
        {
            for(int j = 1; j < pyr.intvs-1; ++j)
            {
                Image *pimg = pyr.imgs+i*pyr.intvs+j;
                for(int y = SIFT_IMG_BORDER; y < pimg->_h-SIFT_IMG_BORDER; ++y)
                {
                    for(int x = SIFT_IMG_BORDER; x < pimg->_w-SIFT_IMG_BORDER; ++x)
                    {
                        double val = pimg->at(y, x);
                        if(fabs(val) > thresh)
                        {
                            ++cnt0;
                            if(is_extremum(pyr, i, j, y, x))
                            {
                                ++cnt1;
                                if(0 == interplate_extremum(pyr, i, j, y, x, 2*thresh, tmp))
                                {
                                    ++cnt2;
                                    if(!like_edge_toomuch(pyr, tmp.octv, tmp.intv, tmp.y, tmp.x, curv_thr))
                                    {
                                        ++cnt3;
                                        keypoints.push_back(tmp);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        logdebug("after thresh: %d", cnt0);
        logdebug("after is_extremum: %d", cnt1);
        logdebug("after interplate_extremum: %d", cnt2);
        logdebug("after like_edge_toomuch: %d", cnt3);
    }


    int interplate_extremum(I const Pyramid& pyr, I const int octv, I int intv, I int y, I int x, I const double contr_thr, O KeyPoint& keypoint)
    {
        int i = 0;
        int h = (pyr.imgs[octv*pyr.intvs])._h, w = (pyr.imgs[octv*pyr.intvs])._w;
        double offset[3] = {0};
        while(i < SIFT_MAX_INTERP_STEPS)
        {
            get_interp_offset(pyr, octv, intv, y, x, offset);
            if(fabs(offset[0]) < 0.5 && fabs(offset[1]) < 0.5 && fabs(offset[2]) < 0.5) break;
            intv += round(offset[0]);
            y += round(offset[1]);
            x += round(offset[2]);

            if( intv <= 0 || intv >= pyr.intvs-1 || y < SIFT_IMG_BORDER || y >= h-SIFT_IMG_BORDER || x < SIFT_IMG_BORDER || x >= w-SIFT_IMG_BORDER)
            {
                return -1;
            }

            ++i;
        }

        if(i >= SIFT_MAX_INTERP_STEPS) return -2;

        double val = 0;
        get_interp_value(pyr, octv, intv, y, x, offset, val);
        if(fabs(val) < contr_thr) return -3;

        keypoint.octv = octv;
        keypoint.intv = intv;
        keypoint.y = y;
        keypoint.x = x;
        keypoint.offset_intv = offset[0];
        keypoint.offset_y = offset[1];
        keypoint.offset_x = offset[2];
        keypoint.dy = (y + offset[1])*pow(2.0, octv);
        keypoint.dx = (x + offset[2])*pow(2.0, octv);
        keypoint.val = (pyr.imgs[octv*pyr.intvs+intv]).at(y, x);

        return 0;
    }

 
    void get_interp_offset(I const Pyramid& pyr, I const int octv, I const int intv, I const int y, I const int x, O double offset[3])
    {
        double dD[3] = {0};
        derive3d(pyr, octv, intv, y, x, dD);
        double dH[9] = {0};
        hessian3d(pyr, octv, intv, y, x, dH);
        double dH_inv[9] = {0};
        inverse3D(dH, dH_inv);
        for(int i = 0; i < 3; ++i)
        {
            offset[i] = 0.0;
            for(int j = 0; j < 3; ++j)
            {
                offset[i] -= dH_inv[i*3 + j] * dD[j];
            }
        }
    }

 
    void get_interp_value(I const Pyramid& pyr, I const int octv, I int intv, I int y, I int x, I double offset[3], O double& val)
    {
        double dD[3] = {0};
        derive3d(pyr, octv, intv, y, x, dD);
        double term = 0.0;
        for(int i = 0; i < 3; ++i)
        {
            term += dD[i] * offset[i];
        }
        val = (pyr.imgs[octv*pyr.intvs+intv]).at(y, x) + 0.5*term;
    }

 
    bool like_edge_toomuch(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, I const int curv_thr)
    {
        Image *pimg = pyr.imgs + octv*pyr.intvs+intv;
        double dyy = pimg->at(y+1, x) + pimg->at(y-1, x) - 2*pimg->at(y, x);
        double dxx = pimg->at(y, x+1) + pimg->at(y, x-1) - 2*pimg->at(y, x);
        double dxy = (pimg->at(y+1, x+1) + pimg->at(y-1, x-1) - pimg->at(y-1, x+1) - pimg->at(y+1, x-1))/4.0;
        double trH = dxx + dyy;
        double detH = dxx*dyy - dxy*dxy;
        if(detH <= 0) return true;
        return (trH*trH)/detH >= ((curv_thr+1)*(curv_thr+1))/curv_thr;
    }

    void calculate_scale(I O vector<KeyPoint>& keypoints, I const double sigma, I const int intvs)
    {
        double intv = 0.0;
        for(int i = 0; i < keypoints.size(); ++i)
        {  
            intv                        = keypoints[i].intv + keypoints[i].offset_intv;
            keypoints[i].scale          = sigma * pow(2.0, keypoints[i].octv + intv/intvs);
            keypoints[i].octv_scale     = sigma * pow(2.0, intv/intvs);
        }
    }

    void downsize_feats(I O vector<KeyPoint>& feats)
    {
        for(int i = 0; i < feats.size(); ++i)
        {  
            feats[i].dx /= 2;
            feats[i].dy /= 2;
            feats[i].scale /= 2;
        }
    }

 
    void derive3d(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, O double derivative[3])
    {
        Image *pimg = pyr.imgs + octv*pyr.intvs+intv;
        Image *pimg_l = pimg-1, *pimg_r = pimg+1;
        derivative[0] = (pimg_r->at(y, x) - pimg_l->at(y, x)) / 2.0;
        derivative[1] = (pimg->at(y+1, x) - pimg->at(y-1, x)) / 2.0;
        derivative[2] = (pimg->at(y, x+1) - pimg->at(y, x-1)) / 2.0;
    }

 
    void hessian3d(I const Pyramid& pyr, I const int octv, I int intv, I const int y, I const int x, O double hessian[9])
    {
        Image *pimg = pyr.imgs + octv*pyr.intvs+intv;
        Image *pimg_l = pimg-1, *pimg_r = pimg+1;
        hessian[0] = pimg_l->at(y, x) + pimg_r->at(y, x) - 2*pimg->at(y, x);
        hessian[4] = pimg->at(y-1, x) + pimg->at(y+1, x) - 2*pimg->at(y, x);
        hessian[8] = pimg->at(y, x-1) + pimg->at(y, x+1) - 2*pimg->at(y, x);
        hessian[1] = hessian[3] = (pimg_l->at(y-1, x) + pimg_r->at(y+1, x) - pimg_l->at(y+1, x) - pimg_r->at(y-1, x))/4.0;
        hessian[2] = hessian[6] = (pimg_l->at(y, x-1) + pimg_r->at(y, x+1) - pimg_l->at(y, x+1) - pimg_r->at(y, x-1))/4.0;
        hessian[5] = hessian[7] = (pimg->at(y-1, x-1) + pimg->at(y+1, x+1) - pimg->at(y-1, x+1) - pimg->at(y+1, x-1))/4.0;
    }
    #define Hd(i, j) (*(H+(i)*3 + (j)))
    #define HId(i, j) (*(H_inv+(i)*3 + (j)))
    bool inverse3D(I const double H[9], O double H_inv[9])
    {
        // determnant
        double detH = Hd(0, 0)*Hd(1, 1)*Hd(2, 2)
                + Hd(0, 1)*Hd(1, 2)*Hd(2, 0)
                + Hd(0, 2)*Hd(1, 0)*Hd(2, 1)
                - Hd(0, 0)*Hd(1, 2)*Hd(2, 1)
                - Hd(0, 1)*Hd(1, 0)*Hd(2, 2)
                - Hd(0, 2)*Hd(1, 1)*Hd(2, 0);

        if(fabs(detH) < 1e-10) return false;

        // adjoint matrix
        HId(0, 0) = Hd(1, 1) * Hd(2, 2) - Hd(1, 2)*Hd(2, 1);
        HId(0, 1) = -(Hd(0, 1) * Hd(2, 2) - Hd(0, 2) * Hd(2, 1));
        HId(0, 2) = Hd(0, 1) * Hd(1, 2) - Hd(0, 2)*Hd(1, 1);
        HId(1, 0) = -(Hd(1, 0) * Hd(2, 2) - Hd(1, 2)*Hd(2, 0));
        HId(1, 1) = Hd(0, 0) * Hd(2, 2) - Hd(0, 2) * Hd(2, 0);
        HId(1, 2) = -(Hd(0, 0) * Hd(1, 2) - Hd(0, 2)*Hd(1, 0));
        HId(2, 0) = Hd(1, 0) * Hd(2, 1) - Hd(1, 1)*Hd(2, 0);
        HId(2, 1) = -(Hd(0, 0) * Hd(2, 1) - Hd(0, 1) * Hd(2, 0));
        HId(2, 2) = Hd(0, 0) * Hd(1, 1) - Hd(0, 1)*Hd(1, 0);

        for(int i = 0; i < 9; ++i) *(H_inv+i) /= detH;

        return true;
    }

 
    void assign_orient(I const Pyramid& gauss_pyr, I vector<KeyPoint>& extrema, I const int bins, O vector<KeyPoint>& feats)
    {
        Hist hist;
        hist.bins = bins;
        for(vector<KeyPoint>::iterator it = extrema.begin(); it != extrema.end(); ++it)
        {
            create_ori_hist(gauss_pyr.imgs[it->octv*gauss_pyr.intvs + it->intv], it->y, it->x, round(SIFT_ORI_WINDOW_RADIUS*it->octv_scale), SIFT_ORI_SIGMA_TIMES*it->octv_scale, hist);
            for(int i = 0; i < SIFT_ORI_SMOOTH_TIMES; ++i)
            {
                gauss_smooth_hist(hist);
            }
            add_feats_by_ori(*it, hist, feats);
        }
    }

 
    void create_ori_hist(I Image& img, I const int y, I const int x, I const int radius, I const double sigma, I O Hist &hist)
    {
        double  mag = 0, ori = 0, wgt = 0, PI2 = 2.0*PI, exp_denom = -1.0/(2.0*sigma*sigma);
        hist.min_mag = 1e16;
        hist.max_mag = 0.0;
        for(int bin = 0, i = -radius; i <= radius; ++i)
        {
            for(int j = -radius; j <= radius; ++j)
            {
                if(calc_mag_ori(img, y+i, x+j, mag, ori))
                {
                    wgt = exp((i*i+j*j)*exp_denom);
                    bin = round(hist.bins * ori/PI2);
                    bin = bin < hist.bins ? bin : 0;
                    hist.mag[bin] += mag * wgt;
                    if(hist.min_mag > hist.mag[bin]) hist.min_mag = hist.mag[bin];
                    if(hist.max_mag < hist.mag[bin]) hist.max_mag = hist.mag[bin];
                }
            }
        }
    }

    void gauss_smooth_hist(I O Hist& hist)
    {
        double prev = hist.mag[hist.bins-1];
        double temp = 0;
        double h0 = hist.mag[0];
        hist.min_mag = 1e16;
        hist.max_mag = 0.0;
        for(int i = 0; i < hist.bins; ++i)
        {
            temp = hist.mag[i];
            hist.mag[i] = 0.25 * prev + 0.5 * hist.mag[i] + 0.25 * (i+1 >= hist.bins ? h0 : hist.mag[i+1]);
            prev = temp;
            if(hist.min_mag > hist.mag[i]) hist.min_mag = hist.mag[i];
            if(hist.max_mag < hist.mag[i]) hist.max_mag = hist.mag[i];
        }
    }

    #define parabola_interp_offset(l, c, r) (0.5*((l)-(r))/((l)-2.0*(c)+(r)))
    void add_feats_by_ori(I const KeyPoint& keypoint, I const Hist& hist, I O vector<KeyPoint>& feats)
    {
        double  bin, PI2 = PI*2.0, mag_thr = SIFT_ORI_PEAK_RATIO*hist.max_mag;
        int l = 0, r = 0;
        for(int i = 0; i < hist.bins; ++i)
        {
            l = (0 == i) ? hist.bins-1 : i-1;
            r = (hist.bins == i+1) ? 0 : i+1;
            if(hist.mag[i] > hist.mag[l] && hist.mag[i] > hist.mag[r] && hist.mag[i] >= mag_thr)
            {
                bin = i + parabola_interp_offset(hist.mag[l], hist.mag[i], hist.mag[r]);
                bin = (bin < 0) ? (bin + hist.bins) : (bin >= hist.bins ? (bin-hist.bins) : bin);
                KeyPoint new_key;
                copy_key_point(keypoint, new_key);
                new_key.ori = PI2 * bin / hist.bins;
                feats.push_back(new_key);
            }
        }
    }

 
    bool calc_mag_ori(I Image& img, I const int y, I const int x, O double &mag, O double &ori)
    {
        if(y <= 0 || y >= img._h-1 || x <= 0 || x >= img._w-1) return false;
        double dy = (img._data[(y+1)*img._w*img._c+x*img._c] - img._data[(y-1)*img._w*img._c+x*img._c]) / 2.0;
        double dx = (img._data[y*img._w*img._c+(x+1)*img._c] - img._data[y*img._w*img._c+(x-1)*img._c]) / 2.0;
        mag = sqrt(dy*dy + dx*dx);
        ori = atan2(dy, dx); if(ori < 0) ori += 2*PI;
        return true;
    }

    void copy_key_point(I const KeyPoint& src, O KeyPoint& dst)
    {
        dst.octv = src.octv;
        dst.intv = src.intv;
        dst.y = src.y;
        dst.x = src.x;
        dst.offset_intv = src.offset_intv;
        dst.offset_y = src.offset_y;
        dst.offset_x = src.offset_x;
        dst.dy = src.dy;
        dst.dx = src.dx;
        dst.scale = src.scale;
        dst.octv_scale = src.octv_scale;
        dst.ori = src.ori;
        dst.val = src.val;
        // dst.descr_length = src.descr_length;
    }
    
 
    void generate_descriptor(I O vector<KeyPoint>& feats, I const Pyramid& gauss_pyr, I const int bins, I const int width)
    {
        for(int i = 0; i < feats.size(); ++i)
        {
            create_descr_hist(gauss_pyr.imgs[feats[i].octv*gauss_pyr.intvs+feats[i].intv], feats[i], bins, width);
        }
    }

 
    void create_descr_hist(I Image& img, I O KeyPoint& feat, I const int bins, I const int width)
    {
        feat.descr_length = width*width*bins;
        double cos_ori = cos(feat.ori);
        double sin_ori = sin(feat.ori);
        double sigma = 0.5 * width;
        double PI2 = 2*PI;
        double exp_denom = -0.5/(sigma*sigma), A = 1.0/(PI2*sigma*sigma);
        double sub_width = SIFT_DESCR_SCALE_ADJUST * feat.octv_scale;
        int radius = round(0.5*sqrt(2.0)*sub_width*(width+1));
        double grad_ori = 0.0, grad_mag = 0.0;
        for(int i = -radius; i <= radius; ++i)
        {
            for(int j =-radius; j <= radius; ++j)
            {
                double rot_y = (cos_ori * i - sin_ori * j);
                double rot_x = (cos_ori * j + sin_ori * i);
                double xbin = rot_x / sub_width + width/2 - 0.5;
                double ybin = rot_y / sub_width + width/2 - 0.5;
    
                if(xbin > -1.0 && xbin < width && ybin > -1.0 && ybin < width)
                {
                    if(calc_mag_ori(img, feat.y+i, feat.x+j, grad_mag, grad_ori))
                    {
                        grad_ori -= feat.ori;
                        if(grad_ori < 0.0) grad_ori += PI2;
                        if(grad_ori >= PI2) grad_ori -= PI2;
                        double zbin = bins * grad_ori / PI2;
                        double weight = A * exp(exp_denom*(rot_x*rot_x + rot_y*rot_y));
                        interp_hist_entry(feat, ybin, xbin, zbin, grad_mag*weight, bins, width);
                    }
                }
            }
        }

        normalize_descr(feat);
        for(int i = 0; i < feat.descr_length; ++i)
        {
            if( feat.descriptor[i] > SIFT_DESCR_MAG_THR)
            {
                feat.descriptor[i] = SIFT_DESCR_MAG_THR;
            }
        }
        normalize_descr(feat);

        for(int i = 0, int_val = 0; i < feat.descr_length; ++i)
        {
            int_val = SIFT_INT_DESCR_FCTR * feat.descriptor[i];
            feat.descriptor[i] = min(255, int_val);
        }
    }

    void interp_hist_entry(I O KeyPoint& feat, I const double ybin, I const double xbin, I const double zbin, I const double mag, I const int bins, I const int width)
    {
        int y0 = floor(ybin), x0 = floor(xbin), z0 = floor(zbin), y, x, z, i, j, k;
        double d_y = ybin-y0, d_x = xbin-x0, d_z = zbin-z0, v_y, v_x, v_z;
        for(i = 0; i <= 1; ++i)
        {
            y = y0 + i;
            if(y >= 0 && y < width)
            {
                v_y = mag * ( (i == 0)? 1.0 - d_y : d_y );
                for(j = 0; j <= 1; ++j)
                {
                    x = x0 + j;
                    if(x >= 0 && x < width)
                    {
                        v_x = v_y * ( (j == 0)? 1.0 - d_x : d_x );
                        for(k = 0; k <= 1; ++k)
                        {
                            z = (z0 + k) % bins;
                            v_z = v_x * ( ( k == 0 )? 1.0 - d_z : d_z );
                            feat.descriptor[y*width*width + x*width + z] += v_z;
                        }
                    }
                }
            }
        }
    }

    void normalize_descr(I O KeyPoint& feat)
    {  
        double cur, root_sum_sq_inv, sum_square = 0.0;
        int i, d = feat.descr_length;

        for(i = 0; i < d; ++i)
        {
            cur = feat.descriptor[i];
            sum_square += cur*cur;
        }

        root_sum_sq_inv = 1.0 / sqrt(sum_square);
        for( i = 0; i < d; ++i)
        {
            feat.descriptor[i] *= root_sum_sq_inv;
        }
    }

    void draw_key_points(Image &img, vector<KeyPoint>& keypoints)
    {
        cv::Mat mat;
        img2cvmat(img, mat);
        cv::Scalar color = {255, 0 ,0};
        for(int i = 0; i < keypoints.size(); ++i)
        {
            cv::circle(mat, cv::Point(keypoints[i].dx, keypoints[i].dy), 3, color);
        }
        cvmat2img(mat, img);
    }

    void draw_sift_features(I Image& img, vector<KeyPoint>& features)
    {  
        cv::Mat mat;
        img2cvmat(img, mat);
        cv::Scalar color = { 0, 0, 255 };
        for(int i = 0; i < features.size(); ++i)
        {  
            draw_sift_feature(mat, features[i], color);
        }
        cvmat2img(mat, img);
    }

    void draw_sift_feature(I cv::Mat& src, KeyPoint& feat, cv::Scalar color)
    {  
        int len, hlen, blen, start_x, start_y, end_x, end_y, h1_x, h1_y, h2_x, h2_y;  
        double scl, ori;  
        double scale = 5.0;  
        double hscale = 0.75;  
        cv::Point start, end, h1, h2;  
    
        /* compute points for an arrow scaled and rotated by feat's scl and ori */  
        start_x = round( feat.dx );  
        start_y = round( feat.dy );  
        scl = feat.scale;  
        ori = feat.ori;  
        len = round( scl * scale );  
        hlen = round( scl * hscale );  
        blen = len - hlen;  
        end_x = round( len *  cos( ori ) ) + start_x;  
        end_y = round( len * -sin( ori ) ) + start_y;  
        h1_x = round( blen *  cos( ori + CV_PI / 18.0 ) ) + start_x;  
        h1_y = round( blen * -sin( ori + CV_PI / 18.0 ) ) + start_y;  
        h2_x = round( blen *  cos( ori - CV_PI / 18.0 ) ) + start_x;  
        h2_y = round( blen * -sin( ori - CV_PI / 18.0 ) ) + start_y;  
        start = cv::Point( start_x, start_y );  
        end = cv::Point( end_x, end_y );  
        h1 = cv::Point( h1_x, h1_y );  
        h2 = cv::Point( h2_x, h2_y );  
    
        line( src, start, end, color, 1, 8, 0 );  
        line( src, end, h1, color, 1, 8, 0 );  
        line( src, end, h2, color, 1, 8, 0 );  
    }

}
