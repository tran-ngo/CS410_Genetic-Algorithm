Trong bài tập BT02 này chúng ta sẽ sử dụng thuật toán NSGA-II và MOEA/D trong thư viện pymoo để giải một số bài toán Tối ưu hóa đa mục tiêu.

* Thư viện: https://pymoo.org/ \
* Link hướng dẫn NSGA-II với pymoo: https://pymoo.org/algorithms/nsga2.html \
* Link hướng dẫn MOEA/D với pymoo: https://pymoo.org/algorithms/moead.html 

Yêu cầu bài nộp:
* Được phép sử dụng thư viện hỗ trợ, tham khảo code hướng dẫn. \
* Random seed: sử dụng MSSV của mình. \
* Các unconstrained problems để test: ZDT1, ZDT2, ZDT3, ZDT4, ZDT6 (https://pymoo.org/problems/multi/zdt.html) \
* Các constrained problems để test: DASCMOP1-6 (https://pymoo.org/problems/constrained/dascmop.html) \
* Thực nghiệm: Hãy thử tune các tham số như population size và số thế hệ (n_gen) của NSGA-II và MOEA/D để so sánh performance của các thuật toán trên từng problem (Cần đảm bảo number_of_evaluations của mỗi thuật toán là như nhau). Tham khảo link sau: https://pymoo.org/misc/performance_indicator.html hiểu cách biểu diễn biên Pareto kết quả thu được còn cách biên Pareto tối ưu bao xa và các độ đo liên quan. 

Báo cáo kết quả: Nộp source code và đồ thị trong 1 file Jupyter notebook. Mỗi thuật toán trên mỗi problem chỉ cần báo cáo 1 lần chạy với random seed là MSSV của mình.
