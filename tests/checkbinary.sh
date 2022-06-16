#!/bin/bash
function test_hybrid-Lambda {
  echo -n " hybrid-Lambda $@ "
  for i in `seq 1 1`; do
    echo -n "."

    if [ -f hybrid-Lambda_dbg ]; then
      # Test using hybrid-Lambda self-checks
      ./hybrid-Lambda_dbg $@ -seed $i > /dev/null
      if [ $? -ne 0 ]; then
        echo ""
        echo "Executing \"./hybrid-Lambda_dbg $@ -seed $i\" failed."
        echo "Debug Call: make -mj2 hybrid-Lambda_dbg && ./hybrid-Lambda_dbg $@ -seed $i 2>&1 | less"
        exit 1
      fi
    fi

    # Test for memory leaks
    valgrind --error-exitcode=1 --leak-check=full -q ./hybrid-Lambda $@ -seed $i > /dev/null
    if [ $? -ne 0 ]; then
      echo ""
      echo "Valgrind check of \"./hybrid-Lambda $@ -seed $i\" failed."
      exit 1
    fi

  done
  echo " done."
}

echo "Testing Examples"
	test_hybrid-Lambda -spcu '((1:1,2:1):1,3:2);' -print
	test_hybrid-Lambda -spcu '((1:1,2:1):1,3:2);' -num 3 -seed 2 -o example1 || exit 1
	test_hybrid-Lambda -spcu trees/4_tax_sp_nt1_para -o example2 -num 2 -mu 0.00003 -sim_mut_unit -sim_num_mut || exit 1
	test_hybrid-Lambda -spcu '((1:1,2:1):1,3:2);' -num 100 -pop 25000 -sim_num_gener || exit 1
	test_hybrid-Lambda -spng '(A:50000,B:50000)r;' -pop '(A:50000,B:50000)r:40000;' || exit 1
	test_hybrid-Lambda -spcu '((((A:1.1,B:1.1):2.1,a:2.2):1.1,13D:.2):.3,4:.3);' -S 2 4 3 6 5 || exit 1
	test_hybrid-Lambda -spcu '(A:1,B:1)r;' -mm '(A:1.9,B:.2)r:2;' -S 3 4 || exit 1
	test_hybrid-Lambda -spcu trees/7_tax_sp_nt1_para -dot -branch || exit 1
	test_hybrid-Lambda -spcu trees/4_tax_sp1.tre -num 1000 -o GENE -f || exit 1
	test_hybrid-Lambda -gt GENE_coal_unit -f  || exit 1
  test_hybrid-Lambda -spcu '((1:1,2:1):1,3:2);' -o GENE -num 100 -mu 0.00003 -sim_num_mut || exit 1
	test_hybrid-Lambda -mt GENE_num_mut -seg  || exit 1
  test_hybrid-Lambda -spcu '(A:5,B:5)r;' -mono -num 100 -mm .1 -S 4 4 || exit 1
  test_hybrid-Lambda -spcu "'((t3:1.123916174,((t4:0.4459935601,((t13:0.02953586373,t7:0.02953586373)I1:0.2529580411,t6:0.2824939049)I2:0.1634996552)I3:0.6268849558,(((t10:0.2528263692,((t5:0.02957738207)H26#0.5164631303:0.2232489871)H24#0.9067618483:0.0)I4:0.1281591885,(((t1:0.02957738207,H26#0.5164631303:0.0)I5:0.2232489871,H24#0.9067618483:0.0)I6:0.1281591885)H20#0.662992664:0.0)I7:0.07706148448,(t12:0.3809855577,H20#0.662992664:0.0)I8:0.07706148448)I9:0.6148314737)I10:0.05103765815)I11:1.604201279,t8:2.728117453)I12;'" -num 100 -seed 6724 || exit 1
  test_hybrid-Lambda -spcu "'(((((t3:0.2637610952,t2:0.2637610952)I1:1.0912968362,(t5:0.2662054335)#H22:1.0888524979)I2:0.2211237452,((#H22:0.1800944633)#H15:1.017267664)#H14:0.1126141157)I3:0.08142212706,#H14:0.1940362428)I4:0.2476537071,(t4:0.4462998968,#H15:0.0)I5:1.458957614)I6;'" -num 6400 -seed 1619 -o gt || exit 1
echo ""
