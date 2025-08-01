ESP x509 证书包
===================

:link_to_translation:`en:[English]`

概述
-----

ESP x509 证书包 API 提供了一种简便的方法，帮助你安装自定义 x509 根证书用于 TLS 服务器验证。

.. note::

    目前在使用 WolfSSL 时该证书包不可用。

该证书包中包括 Mozilla NSS 根证书存储区的完整根证书列表。使用 gen_crt_bundle.py python 程序，可将证书的主题名称和公钥存储在文件中，并嵌入 {IDF_TARGET_NAME} 二进制文件。

生成证书包时，你需选择：

* 来自 Mozilla 的完整根证书包，包含超过 130 份证书。目前提供的证书包更新于 2025 年 5 月 20 日，星期天, 03:12:02 (GMT)。
* 一组预先筛选的常用根证书。其中仅包含约 38 份证书，但根据 SSL 证书颁发机构统计数据，其绝对使用率约达到 93%，市场覆盖率约达 99%。

此外，还可指定证书文件的路径或包含证书的目录，将其他证书添加到生成的证书包中。

.. note::

    信任所有根证书意味着如果任何证书被收回，就必须更新证书列表，包括从 ``cacrt_all.pem`` 中将其删除。

配置
------

多数配置可通过 menuconfig 完成。CMake 会根据配置信息生成及嵌入证书包。

 * :ref:`CONFIG_MBEDTLS_CERTIFICATE_BUNDLE`：自动创建并附加证书包。
 * :ref:`CONFIG_MBEDTLS_DEFAULT_CERTIFICATE_BUNDLE`：决定添加证书列表中的哪些证书。
 * :ref:`CONFIG_MBEDTLS_CUSTOM_CERTIFICATE_BUNDLE_PATH`：指定要在证书包中嵌入的其他证书的路径。

要在使用 ESP-TLS 时启用证书包，将函数指针指向证书包的 attach 函数：

.. code-block:: c

    esp_tls_cfg_t cfg = {
         .crt_bundle_attach = esp_crt_bundle_attach,
    };

此步骤是为了避免在用户未使能的情况下嵌入证书包。

如果直接使用 mbedTLS 包，在设置阶段直接调用 attach 函数可以激活证书包：

.. code-block:: c

    mbedtls_ssl_config conf;
    mbedtls_ssl_config_init(&conf);

    esp_crt_bundle_attach(&conf);


.. _updating_bundle:

生成根证书列表
----------------

根证书列表来自 Mozilla 的 `NSS 根证书商店 <https://wiki.mozilla.org/CA/Included_Certificates>`_。

运行 ``mk-ca-bundle.pl`` 脚本可下载和创建列表。脚本发布于 `curl <https://github.com/curl/curl>`_。

还可通过 curl 网站直接下载完整列表： `从 Mozilla 提取的 CA 证书 <https://curl.se/docs/caextract.html>`_。

常用证书包是通过筛选出市场份额超过 1% 的授权机构来决定的，筛选数据来自 w3tech 的 `SSL Survey <https://w3techs.com/technologies/overview/ssl_certificate>`_。

根据这些授权机构，从 Mozilla 提供的 `列表 <https://ccadb-public.secure.force.com/mozilla/IncludedCACertificateReportPEMCSV>`_ 的 ``cmn_crt_authorities.csv`` 中筛选证书名称。


更新证书包
------------

证书包嵌入到应用程序中，通过 OTA 更新与应用程序一起更新。如果想使用比目前 ESP-IDF 中的证书包更新的包，则可按照 :ref:`updating_bundle` 中的说明从 Mozilla 下载证书列表。


定期同步
-------------

证书包会与 Mozilla 的 NSS 根证书商店定期同步。在 ESP-IDF 的次要版本或补丁版本中，为了保证兼容性，会将上游证书包中已弃用的证书添加到弃用列表。如有需要，可以通过 :ref:`CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_DEPRECATED_LIST` 将弃用证书加入默认证书包。这些弃用证书将在下一个 ESP-IDF 主要版本中移除。

交叉签名证书支持
----------------

概述
^^^^

启用配置选项 :ref:`CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_CROSS_SIGNED_VERIFY` 时，ESP x509 证书包 API 将支持验证包含交叉签名根证书的证书链。

即使证书链中包含交叉签名根证书，验证过程中也能从证书包中智能匹配候选的证书颁发机构 (CA)，从而提高与各类服务器证书的互操作性。

启用该功能后，证书验证逻辑与默认的 mbedTLS 行为一致，能够确保与交叉签名证书链兼容，且验证过程稳健可靠。

.. note::

    启用交叉签名证书支持功能后，运行时的堆内存使用量将增加约 700 字节，但由于证书包体积减小，flash 占用会降低。

关键点：

- 证书包可作为动态 CA 存储，在握手过程中提供候选的根证书；
- 验证回调函数会使用证书链中的颁发者信息，从证书包中定位并提供匹配的根证书；
- 该功能在交叉签名较为常见的场景中能够提供帮助，例如根 CA 切换期间。

使用方法
^^^^^^^^

除了在项目配置中启用 :ref:`CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_CROSS_SIGNED_VERIFY` 外，应用无需额外更改。握手过程中，证书包会自动提供候选的 CA。

.. note::

    如果启用了 :ref:`CONFIG_MBEDTLS_CERTIFICATE_BUNDLE_CROSS_SIGNED_VERIFY`，其内部会使用 ``MBEDTLS_X509_TRUSTED_CERT_CALLBACK``。在此情况下，用户 **不应** 自行提供受信任证书回调函数，因为证书包会自动处理。

应用示例
---------

:example:`protocols/https_x509_bundle` 演示了如何使用 ESP-TLS 创建安全套接字连接的简单 HTTPS 示例，该示例使用了证书包并添加了两个自定义证书用于验证。

:example:`protocols/https_request` 演示了如何使用 ESP-TLS 和默认证书包的 HTTPS 示例。

:example:`protocols/https_mbedtls` 演示了如何使用 Mbed TLS 和默认证书包的 HTTPS 示例。

API 参考
----------

.. include-build-file:: inc/esp_crt_bundle.inc
