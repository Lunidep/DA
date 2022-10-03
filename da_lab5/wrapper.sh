#! /usr/bin/env bash

set -o errexit
set -o pipefail
set -o nounset

readonly TESTS_DIR=tests

function log_info()
{
	log_ "info" "$@"
}

function log_error()
{
	log_ "error" "$@" 
}

function log_()
{
	local type=$1
	local messange=$2
	local date_str=; date_str=$(date)
	echo "[${type}][${date_str}] ${messange}"
}

function main() {

	local bin_prog=da_lab5
    local bin_bench=benchmark

    local test_name="test"
    local bench_test_name="test_bench"


	log_info "Stage #1. Compiling..."
	if ! make ; then
		log_error "Failed to compile da_lab4.cpp"
		return 1
	fi
	log_info "Compiling OK"


	log_info "Stage #2. Benchmark generating..."
	if ! python3 generator.py ; then
		log_error "Failed benchmark generating"
		return 1
	fi 
	log_info "Benchmark generating OK"


    log_info "Stage #3. Program testing..."
	if ! ./${bin_prog} < ${test_name}; then
		log_error "Failed benchmark generating"
		return 1
	fi 
	log_info "Program testing OK"

	log_info "Stage #4. Benchmark results:"
	if ! ./${bin_bench} < ${bench_test_name}; then
        log_error "Failed to run benchmark test"
        return 1
    fi
	log_info "Benchmark OK"
}

main $@