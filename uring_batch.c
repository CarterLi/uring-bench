#include <liburing.h>

int main() {
  struct io_uring ring;
  io_uring_queue_init(64, &ring, 0);

  static char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 999999; i++) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    if (!sqe)
    {
      io_uring_submit_and_wait(&ring, 64);
      io_uring_cq_advance(&ring, io_uring_cq_ready(&ring));
      sqe = io_uring_get_sqe(&ring);
    }
    io_uring_prep_write(sqe, STDOUT_FILENO, &str[i % 26], 1, 0);
    io_uring_sqe_set_flags(sqe, IOSQE_IO_LINK);
  }
  io_uring_submit_and_wait(&ring, 1);

  io_uring_queue_exit(&ring);
}
