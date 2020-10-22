#include "blobfuse.cpp"


int main(int argc, char *argv[])
{
    static struct fuse_operations azs_blob_operations;
    set_up_callbacks(azs_blob_operations);

    struct fuse_args args;
    int ret = read_and_set_arguments(argc, argv, &args);
    if (ret != 0)
    {
        return ret;
    }
    // commenting out the below as it is to take care of non-thread safe for gnutls before 3.3
    //ret = configure_tls();
    if (ret != 0)
    {
        return ret;
    }

    configure_fuse(&args);

    ret = initialize_blobfuse();
    if (ret != 0)
    {
        return ret;
    }

    ret =  fuse_main(args.argc, args.argv, &azs_blob_operations, NULL);

//see gnutls comment above
   // gnutls_global_deinit();

    return ret;
}
